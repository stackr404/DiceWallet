#include "coins/hd_coins.h"
#include "app/passphrase_limits.h"

#include <stdio.h>
#include <string.h>

#include <esp_random.h>
#include "mbedtls/sha256.h"
#include "mbedtls/md.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/ecp.h"
#include "mbedtls/bignum.h"
#include "mbedtls/ripemd160.h"


#ifndef MBEDTLS_ECP_DP_SECP256K1_ENABLED
#error "Enable CONFIG_MBEDTLS_ECP_DP_SECP256K1_ENABLED. BIP32 secp256k1 cannot run without it."
#endif

#ifndef HD_XPUB_DEBUG
#define HD_XPUB_DEBUG 0
#endif

#if HD_XPUB_DEBUG
#define HD_FAIL(step, code) do { \
    Serial.printf("derive_account_xpub FAIL %s ret=%d\n", step, (int)(code)); \
    return String(""); \
} while (0)
#else
#define HD_FAIL(step, code) return String("")
#endif

static const char *BASE58_CHARS =
    "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

static const uint8_t SECP256K1_N[32] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B,
    0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41
};

// ---------------------------------------------------------------------------
// Registry
// ---------------------------------------------------------------------------
#define VB_XPUB {0x04, 0x88, 0xB2, 0x1E}
#define VB_ZPUB {0x04, 0xB2, 0x47, 0x46}

extern const hd_watch_coin hd_coin_BTC = { "BTC",  "Bitcoin", "zpub", "",  84, 0, VB_ZPUB, HD_ALGO_BIP32_SECP256K1, true,  "m/84'/0'/0'" };
extern const hd_watch_coin hd_coin_ETH = { "ETH",  "Ethereum", "xpub", "",  44,    60, VB_XPUB, HD_ALGO_BIP32_SECP256K1, true,  "m/44'/60'/0'" };
extern const hd_watch_coin hd_coin_XRP = { "XRP",  "XRP", "xpub", "",  44,   144, VB_XPUB, HD_ALGO_BIP32_SECP256K1, true,  "m/44'/144'/0'" };


size_t hd_coin_format_path(char* out, size_t out_len, const hd_watch_coin& coin, uint32_t account) {
    if (!out || out_len < 8) return 0;
    int n = snprintf(out, out_len, "m/%u'/%u'/%u'",
                     (unsigned)coin.purpose,
                     (unsigned)coin.coin_type,
                     (unsigned)account);
    if (n < 0 || (size_t)n >= out_len) {
        if (out_len) out[0] = '\0';
        return 0;
    }
    return (size_t)n;
}

// ---------------------------------------------------------------------------
// Crypto internals (file-local)
// ---------------------------------------------------------------------------

static int zpub_rng(void* /*ctx*/, unsigned char* buf, size_t len) {
    esp_fill_random(buf, len);
    return 0;
}

static void secure_wipe(void *ptr, size_t len) {
    volatile uint8_t *p = static_cast<volatile uint8_t *>(ptr);
    while (len--) *p++ = 0;
}

static bool hmac_sha_512(const uint8_t* key, size_t keyLen, const uint8_t* data, size_t dataLen, uint8_t* output) {
    const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
    if (!md_info) return false;

    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    if (mbedtls_md_setup(&ctx, md_info, 1) != 0 ||
        mbedtls_md_hmac_starts(&ctx, key, keyLen) != 0 ||
        mbedtls_md_hmac_update(&ctx, data, dataLen) != 0 ||
        mbedtls_md_hmac_finish(&ctx, output) != 0) {
        mbedtls_md_free(&ctx);
        return false;
    }
    mbedtls_md_free(&ctx);
    return true;
}

static bool derive_hardened_child(const uint8_t* parentPriv, const uint8_t* parentChain,
                                uint32_t index, uint8_t* childPriv, uint8_t* childChain) {
    uint8_t dataBuffer[1 + 32 + 4];
    dataBuffer[0] = 0x00;
    memcpy(&dataBuffer[1], parentPriv, 32);
    dataBuffer[33] = (uint8_t)(index >> 24);
    dataBuffer[34] = (uint8_t)(index >> 16);
    dataBuffer[35] = (uint8_t)(index >> 8);
    dataBuffer[36] = (uint8_t)(index & 0xFF);

    uint8_t hmacOut[64];
    if (!hmac_sha_512(parentChain, 32, dataBuffer, sizeof(dataBuffer), hmacOut)) {
        secure_wipe(dataBuffer, sizeof(dataBuffer));
        return false;
    }
    secure_wipe(dataBuffer, sizeof(dataBuffer));

    mbedtls_mpi il, kpar, n, ki;
    mbedtls_mpi_init(&il);
    mbedtls_mpi_init(&kpar);
    mbedtls_mpi_init(&n);
    mbedtls_mpi_init(&ki);

    int ret = 0;
    if ((ret = mbedtls_mpi_read_binary(&il, hmacOut, 32)) != 0 ||
        (ret = mbedtls_mpi_read_binary(&kpar, parentPriv, 32)) != 0 ||
        (ret = mbedtls_mpi_read_binary(&n, SECP256K1_N, 32)) != 0 ||
        mbedtls_mpi_cmp_mpi(&il, &n) >= 0 ||
        (ret = mbedtls_mpi_add_mpi(&ki, &il, &kpar)) != 0 ||
        (ret = mbedtls_mpi_mod_mpi(&ki, &ki, &n)) != 0 ||
        mbedtls_mpi_cmp_int(&ki, 0) == 0 ||
        (ret = mbedtls_mpi_write_binary(&ki, childPriv, 32)) != 0) {
        mbedtls_mpi_free(&il); mbedtls_mpi_free(&kpar); mbedtls_mpi_free(&n); mbedtls_mpi_free(&ki);
        secure_wipe(hmacOut, sizeof(hmacOut));
        return false;
    }

    mbedtls_mpi_free(&il);
    mbedtls_mpi_free(&kpar);
    mbedtls_mpi_free(&n);
    mbedtls_mpi_free(&ki);
    memcpy(childChain, &hmacOut[32], 32);
    secure_wipe(hmacOut, sizeof(hmacOut));
    return true;
}

static bool compute_hash_160(const uint8_t* data, size_t len, uint8_t* output) {
    uint8_t sha256_res[32];
    mbedtls_sha256_context sha_ctx;
    mbedtls_sha256_init(&sha_ctx);
    mbedtls_sha256_starts(&sha_ctx, 0);
    mbedtls_sha256_update(&sha_ctx, data, len);
    mbedtls_sha256_finish(&sha_ctx, sha256_res);
    mbedtls_sha256_free(&sha_ctx);
    const int ret = mbedtls_ripemd160(sha256_res, 32, output);
    secure_wipe(sha256_res, sizeof(sha256_res));
    return ret == 0;
}

static int priv_to_compressed_pub(const uint8_t priv[32], uint8_t out33[33],
                               mbedtls_ecp_group* secp, mbedtls_ecp_point* Q, mbedtls_mpi* d) {
    unsigned char uncompressed[65];
    size_t olen = 0;
    int ret = mbedtls_mpi_read_binary(d, priv, 32);
    if (ret != 0) return ret;

    do {
        ret = mbedtls_ecp_mul(secp, Q, d, &secp->G, zpub_rng, nullptr);
    } while (ret == MBEDTLS_ERR_ECP_IN_PROGRESS);
    if (ret != 0) return ret;

    ret = mbedtls_ecp_point_write_binary(secp, Q, MBEDTLS_ECP_PF_UNCOMPRESSED,
                                         &olen, uncompressed, sizeof(uncompressed));
    if (ret != 0 || olen != 65) return ret != 0 ? ret : -1;

    out33[0] = (uncompressed[64] & 1) ? 0x03 : 0x02;
    memcpy(out33 + 1, uncompressed + 1, 32);
    return 0;
}

String encode_base58_check(const uint8_t* input, size_t len) {
    uint8_t hash1[32];
    uint8_t hash2[32];
    mbedtls_sha256_context sha_ctx;
    mbedtls_sha256_init(&sha_ctx);
    mbedtls_sha256_starts(&sha_ctx, 0);
    mbedtls_sha256_update(&sha_ctx, input, len);
    mbedtls_sha256_finish(&sha_ctx, hash1);
    mbedtls_sha256_starts(&sha_ctx, 0);
    mbedtls_sha256_update(&sha_ctx, hash1, 32);
    mbedtls_sha256_finish(&sha_ctx, hash2);
    mbedtls_sha256_free(&sha_ctx);

    const size_t totalLen = len + 4;
    uint8_t tempBuffer[96];
    uint8_t divBuffer[96];
    if (totalLen > sizeof(tempBuffer)) return String("");

    memcpy(tempBuffer, input, len);
    memcpy(tempBuffer + len, hash2, 4);

    char resultStr[128];
    size_t resultIdx = sizeof(resultStr);
    resultStr[--resultIdx] = '\0';

    size_t zeroes = 0;
    while (zeroes < totalLen && tempBuffer[zeroes] == 0) zeroes++;

    memcpy(divBuffer, tempBuffer, totalLen);
    size_t startIdx = zeroes;
    while (startIdx < totalLen) {
        uint32_t remainder = 0;
        for (size_t i = startIdx; i < totalLen; i++) {
            uint32_t current = remainder * 256u + divBuffer[i];
            divBuffer[i] = (uint8_t)(current / 58u);
            remainder = current % 58u;
        }
        resultStr[--resultIdx] = BASE58_CHARS[remainder];
        if (divBuffer[startIdx] == 0) startIdx++;
    }
    while (zeroes-- > 0) resultStr[--resultIdx] = '1';
    return String(resultStr + resultIdx);
}

static void free_ecp(mbedtls_mpi* d, mbedtls_ecp_point* Q, mbedtls_ecp_group* secp) {
    mbedtls_mpi_free(d);
    mbedtls_ecp_point_free(Q);
    mbedtls_ecp_group_free(secp);
}

// ---------------------------------------------------------------------------
// Public derivation
// ---------------------------------------------------------------------------
String derive_account_xpub(const wallet_generation_result& wallet,
                         const String& passphrase,
                         const hd_watch_coin& coin,
                         uint32_t account) {
    if (coin.algo != HD_ALGO_BIP32_SECP256K1 || !coin.this_firmware) {
        HD_FAIL("unsupported HD_WATCH_COINS row", (int)coin.algo);
    }

    if (!wallet.success)
        return String();

    // Stack phrase, not Arduino String: the heap copy was not wiped.
    char mnemonic[256];
    size_t mlen = 0;
    mnemonic[0] = '\0';
    for (int i = 0; i < 24; ++i) {
        const char *word = wallet.mnemonic_24_words[i];
        if (word == nullptr) {
            secure_wipe(mnemonic, sizeof(mnemonic));
            return String();
        }
        if (i > 0) {
            if (mlen + 1 >= sizeof(mnemonic)) {
                secure_wipe(mnemonic, sizeof(mnemonic));
                return String();
            }
            mnemonic[mlen++] = ' ';
        }
        const size_t wlen = strlen(word);
        if (mlen + wlen >= sizeof(mnemonic)) {
            secure_wipe(mnemonic, sizeof(mnemonic));
            return String();
        }
        memcpy(mnemonic + mlen, word, wlen);
        mlen += wlen;
        mnemonic[mlen] = '\0';
    }
    if (mlen == 0) {
        secure_wipe(mnemonic, sizeof(mnemonic));
        HD_FAIL("empty mnemonic", 0);
    }

    // BIP39 salt is "mnemonic" + NFKD(passphrase). This firmware has no NFKD
    // implementation, so non-ASCII passphrases are rejected instead of silently
    // diverging from other wallets. Empty passphrase is the BIP39 default.
    for (size_t i = 0; i < passphrase.length(); ++i) {
        const unsigned char c = static_cast<unsigned char>(passphrase[i]);
        if (c < 0x20 || c > 0x7E) {
            secure_wipe(mnemonic, sizeof(mnemonic));
            HD_FAIL("passphrase must be ASCII until NFKD is implemented", 0);
        }
    }

    char saltStr[8 + kPassphraseMax];
    if (passphrase.length() > static_cast<unsigned>(kPassphraseMax)) {
        secure_wipe(mnemonic, sizeof(mnemonic));
        HD_FAIL("passphrase too long", 0);
    }
    memcpy(saltStr, "mnemonic", 8);
    memcpy(saltStr + 8, passphrase.c_str(), passphrase.length());
    const size_t saltLen = 8 + passphrase.length();

    uint8_t seed[64];
    int ret = mbedtls_pkcs5_pbkdf2_hmac_ext(
        MBEDTLS_MD_SHA512,
        reinterpret_cast<const unsigned char*>(mnemonic), mlen,
        reinterpret_cast<const unsigned char*>(saltStr), saltLen,
        2048, 64, seed);
    secure_wipe(mnemonic, sizeof(mnemonic));
    secure_wipe(saltStr, sizeof(saltStr));
    if (ret != 0) {
        secure_wipe(seed, sizeof(seed));
        HD_FAIL("pbkdf2", ret);
    }

    uint8_t masterHmac[64];
    if (!hmac_sha_512(reinterpret_cast<const uint8_t*>("Bitcoin seed"), 12, seed, 64, masterHmac)) {
        secure_wipe(seed, sizeof(seed));
        HD_FAIL("hmac Bitcoin seed", 0);
    }
    secure_wipe(seed, sizeof(seed));

    uint8_t key[32];
    uint8_t chain[32];
    memcpy(key, masterHmac, 32);
    memcpy(chain, masterHmac + 32, 32);
    secure_wipe(masterHmac, sizeof(masterHmac));

    if (!derive_hardened_child(key, chain, hd_hardened(coin.purpose),  key, chain)) {
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        HD_FAIL("ckd purpose'", 0);
    }
    if (!derive_hardened_child(key, chain, hd_hardened(coin.coin_type), key, chain)) {
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        HD_FAIL("ckd coin_type'", 0);
    }

    mbedtls_ecp_group secp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;
    mbedtls_ecp_group_init(&secp);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&d);

    ret = mbedtls_ecp_group_load(&secp, MBEDTLS_ECP_DP_SECP256K1);
    if (ret != 0) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        HD_FAIL("ecp_group_load secp256k1", ret);
    }

    uint8_t parentPubKey[33];
    ret = priv_to_compressed_pub(key, parentPubKey, &secp, &Q, &d);
    if (ret != 0) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        secure_wipe(parentPubKey, sizeof(parentPubKey));
        HD_FAIL("parent priv->pub", ret);
    }

    uint8_t hash160Out[20];
    if (!compute_hash_160(parentPubKey, 33, hash160Out)) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        secure_wipe(parentPubKey, sizeof(parentPubKey));
        HD_FAIL("hash160 parent fingerprint", 0);
    }
    secure_wipe(parentPubKey, sizeof(parentPubKey));
    uint8_t parentFingerprint[4];
    memcpy(parentFingerprint, hash160Out, 4);

    if (!derive_hardened_child(key, chain, hd_hardened(account), key, chain)) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(key, sizeof(key));
        secure_wipe(chain, sizeof(chain));
        HD_FAIL("ckd account'", 0);
    }

    uint8_t accPubKey[33];
    ret = priv_to_compressed_pub(key, accPubKey, &secp, &Q, &d);
    secure_wipe(key, sizeof(key));
    if (ret != 0) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(chain, sizeof(chain));
        secure_wipe(accPubKey, sizeof(accPubKey));
        HD_FAIL("account priv->pub", ret);
    }

    free_ecp(&d, &Q, &secp);

    uint8_t serialData[78];
    memcpy(&serialData[0], coin.version, 4);
    serialData[4] = 3;
    memcpy(&serialData[5], parentFingerprint, 4);

    uint32_t childIndex = hd_hardened(account);
    serialData[9]  = (uint8_t)(childIndex >> 24);
    serialData[10] = (uint8_t)(childIndex >> 16);
    serialData[11] = (uint8_t)(childIndex >> 8);
    serialData[12] = (uint8_t)(childIndex & 0xFF);

    memcpy(&serialData[13], chain, 32);
    memcpy(&serialData[45], accPubKey, 33);
    secure_wipe(chain, sizeof(chain));
    secure_wipe(accPubKey, sizeof(accPubKey));

    String xpub = encode_base58_check(serialData, 78);
    secure_wipe(serialData, sizeof(serialData));
    if (xpub.length() == 0) HD_FAIL("base58check", 0);
    return xpub;
}

bool hd_mnemonic_to_seed(const char* mnemonic, const char* passphrase, uint8_t seed_out[64]) {
    if (!mnemonic || !seed_out) return false;
    if (!passphrase) passphrase = "";
    const size_t mlen = strlen(mnemonic);
    const size_t plen = strlen(passphrase);
    if (plen > static_cast<size_t>(kPassphraseMax)) return false;
    for (size_t i = 0; i < plen; ++i) {
        const unsigned char c = static_cast<unsigned char>(passphrase[i]);
        if (c < 0x20 || c > 0x7E) return false;
    }
    char saltStr[8 + kPassphraseMax];
    memcpy(saltStr, "mnemonic", 8);
    memcpy(saltStr + 8, passphrase, plen);
    const int ret = mbedtls_pkcs5_pbkdf2_hmac_ext(
        MBEDTLS_MD_SHA512,
        reinterpret_cast<const unsigned char*>(mnemonic), mlen,
        reinterpret_cast<const unsigned char*>(saltStr), 8 + plen,
        2048, 64, seed_out);
    secure_wipe(saltStr, sizeof(saltStr));
    return ret == 0;
}

static bool parse_path_index(const char* text, size_t len, uint32_t* index) {
    if (len == 0) return false;
    bool hardened = false;
    if (text[len - 1] == '\'' || text[len - 1] == 'h' || text[len - 1] == 'H') {
        hardened = true;
        len--;
    }
    if (len == 0) return false;
    uint32_t value = 0;
    for (size_t i = 0; i < len; ++i) {
        if (text[i] < '0' || text[i] > '9') return false;
        const uint32_t digit = static_cast<uint32_t>(text[i] - '0');
        if (value > (0x7fffffffu - digit) / 10u) return false;
        value = value * 10u + digit;
    }
    *index = hardened ? hd_hardened(value) : value;
    return true;
}

static bool derive_normal_child(const uint8_t* parentPriv, const uint8_t* parentChain,
                              const uint8_t parentPub[33], uint32_t index,
                              uint8_t* childPriv, uint8_t* childChain) {
    uint8_t dataBuffer[33 + 4];
    memcpy(dataBuffer, parentPub, 33);
    dataBuffer[33] = (uint8_t)(index >> 24);
    dataBuffer[34] = (uint8_t)(index >> 16);
    dataBuffer[35] = (uint8_t)(index >> 8);
    dataBuffer[36] = (uint8_t)(index & 0xFF);
    uint8_t hmacOut[64];
    if (!hmac_sha_512(parentChain, 32, dataBuffer, sizeof(dataBuffer), hmacOut)) {
        secure_wipe(dataBuffer, sizeof(dataBuffer));
        return false;
    }
    secure_wipe(dataBuffer, sizeof(dataBuffer));
    mbedtls_mpi il, kpar, n, ki;
    mbedtls_mpi_init(&il);
    mbedtls_mpi_init(&kpar);
    mbedtls_mpi_init(&n);
    mbedtls_mpi_init(&ki);
    int ret = 0;
    const bool ok =
        (ret = mbedtls_mpi_read_binary(&il, hmacOut, 32)) == 0 &&
        (ret = mbedtls_mpi_read_binary(&kpar, parentPriv, 32)) == 0 &&
        (ret = mbedtls_mpi_read_binary(&n, SECP256K1_N, 32)) == 0 &&
        mbedtls_mpi_cmp_mpi(&il, &n) < 0 &&
        (ret = mbedtls_mpi_add_mpi(&ki, &il, &kpar)) == 0 &&
        (ret = mbedtls_mpi_mod_mpi(&ki, &ki, &n)) == 0 &&
        mbedtls_mpi_cmp_int(&ki, 0) != 0 &&
        (ret = mbedtls_mpi_write_binary(&ki, childPriv, 32)) == 0;
    mbedtls_mpi_free(&il);
    mbedtls_mpi_free(&kpar);
    mbedtls_mpi_free(&n);
    mbedtls_mpi_free(&ki);
    if (!ok) {
        secure_wipe(hmacOut, sizeof(hmacOut));
        return false;
    }
    memcpy(childChain, &hmacOut[32], 32);
    secure_wipe(hmacOut, sizeof(hmacOut));
    return true;
}

static String serialize_node(const uint8_t version[4], uint8_t depth,
                            const uint8_t fingerprint[4], uint32_t index,
                            const uint8_t chain[32], const uint8_t key33[33]) {
    uint8_t serialData[78];
    memcpy(&serialData[0], version, 4);
    serialData[4] = depth;
    memcpy(&serialData[5], fingerprint, 4);
    serialData[9] = (uint8_t)(index >> 24);
    serialData[10] = (uint8_t)(index >> 16);
    serialData[11] = (uint8_t)(index >> 8);
    serialData[12] = (uint8_t)(index & 0xFF);
    memcpy(&serialData[13], chain, 32);
    memcpy(&serialData[45], key33, 33);
    String encoded = encode_base58_check(serialData, 78);
    secure_wipe(serialData, sizeof(serialData));
    return encoded;
}

struct DerivedNode {
    bool ok;
    uint8_t depth;
    uint8_t fingerprint[4];
    uint32_t index;
    uint8_t chain[32];
    uint8_t key[32];
};

static DerivedNode derive_node_from_seed(const uint8_t* seed, size_t seed_len, const char* path) {
    DerivedNode node = {};
    if (!seed || !path || seed_len == 0 || seed_len > 64) return node;
    if (path[0] != 'm' || (path[1] != '\0' && path[1] != '/')) return node;

    uint8_t masterHmac[64];
    if (!hmac_sha_512(reinterpret_cast<const uint8_t*>("Bitcoin seed"), 12, seed, seed_len, masterHmac)) {
        return node;
    }
    memcpy(node.key, masterHmac, 32);
    memcpy(node.chain, masterHmac + 32, 32);
    secure_wipe(masterHmac, sizeof(masterHmac));

    mbedtls_ecp_group secp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;
    mbedtls_ecp_group_init(&secp);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&d);
    if (mbedtls_ecp_group_load(&secp, MBEDTLS_ECP_DP_SECP256K1) != 0) {
        free_ecp(&d, &Q, &secp);
        secure_wipe(node.key, sizeof(node.key));
        secure_wipe(node.chain, sizeof(node.chain));
        return node;
    }

    const char* cursor = path + 1;
    while (*cursor == '/') {
        cursor++;
        const char* start = cursor;
        while (*cursor && *cursor != '/') cursor++;
        uint32_t index = 0;
        if (!parse_path_index(start, static_cast<size_t>(cursor - start), &index)) {
            free_ecp(&d, &Q, &secp);
            secure_wipe(node.key, sizeof(node.key));
            secure_wipe(node.chain, sizeof(node.chain));
            return node;
        }
        uint8_t parentPub[33];
        uint8_t hash160Out[20];
        if (priv_to_compressed_pub(node.key, parentPub, &secp, &Q, &d) != 0 ||
            !compute_hash_160(parentPub, 33, hash160Out)) {
            free_ecp(&d, &Q, &secp);
            secure_wipe(node.key, sizeof(node.key));
            secure_wipe(node.chain, sizeof(node.chain));
            secure_wipe(parentPub, sizeof(parentPub));
            secure_wipe(hash160Out, sizeof(hash160Out));
            return node;
        }
        memcpy(node.fingerprint, hash160Out, 4);
        secure_wipe(hash160Out, sizeof(hash160Out));
        const bool hardened = (index & 0x80000000u) != 0;
        const bool derived = hardened
            ? derive_hardened_child(node.key, node.chain, index, node.key, node.chain)
            : derive_normal_child(node.key, node.chain, parentPub, index, node.key, node.chain);
        secure_wipe(parentPub, sizeof(parentPub));
        if (!derived) {
            free_ecp(&d, &Q, &secp);
            secure_wipe(node.key, sizeof(node.key));
            secure_wipe(node.chain, sizeof(node.chain));
            return node;
        }
        node.index = index;
        node.depth++;
    }

    free_ecp(&d, &Q, &secp);
    node.ok = true;
    return node;
}

String hd_derive_xpub(const uint8_t* seed, size_t seed_len, const char* path, const uint8_t version[4]) {
    if (!version) return String("");
    DerivedNode node = derive_node_from_seed(seed, seed_len, path);
    if (!node.ok) return String("");

    mbedtls_ecp_group secp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;
    mbedtls_ecp_group_init(&secp);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&d);
    uint8_t pub[33];
    int ret = mbedtls_ecp_group_load(&secp, MBEDTLS_ECP_DP_SECP256K1);
    if (ret == 0) ret = priv_to_compressed_pub(node.key, pub, &secp, &Q, &d);
    free_ecp(&d, &Q, &secp);
    secure_wipe(node.key, sizeof(node.key));
    if (ret != 0) {
        secure_wipe(node.chain, sizeof(node.chain));
        secure_wipe(pub, sizeof(pub));
        return String("");
    }
    String encoded = serialize_node(version, node.depth, node.fingerprint, node.index, node.chain, pub);
    secure_wipe(node.chain, sizeof(node.chain));
    secure_wipe(pub, sizeof(pub));
    return encoded;
}