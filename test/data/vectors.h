#pragma once
// Golden vectors for host and on-device tests.
// BIP39 all-zero entropy is the published "abandon ... art" phrase.
// dice_ones is SHA-256("D6" || 0x01 || 100 || 100 bytes of face 1).
// Account xpubs are m/purpose'/coin'/0' with an empty BIP39 passphrase,
// checked against BIP32 test vector 1's master-key step.

static const char kAbandonPhrase[] =
    "abandon abandon abandon abandon abandon abandon abandon abandon "
    "abandon abandon abandon abandon abandon abandon abandon abandon "
    "abandon abandon abandon abandon abandon abandon abandon art";

static const char* passphrase1 = "MyPassphrase";

static const char kDiceOnesPhrase[] =
    "visa apart possible gather middle sustain tragic sponsor twist often pig protect "
    "among judge box tooth lava seek odor step benefit curve enter verify";

static const char* passphrase2 = "ThePassphrase";

static const char kRandomPhrase[] =
    "visa apart possible gather middle sustain tragic sponsor "
    "twist often pig protect among judge box tooth "
    "lava seek odor step benefit curve enter verify";

struct AccountXpubVector {
  const char* id;
  const char* mnemonic;
  const char* passhrase;
  const char* coin;  // BTC, ETH, XRP
  const char* path;
  const char* xpub;
};

static const AccountXpubVector kAccountXpubVectors[] = {
    {"abandon_btc", kAbandonPhrase, "", "BTC", "m/84'/0'/0'",
     "zpub6qTBTNftBzVTjgVcSUw7vW5N1KQbV93Jnrw314RHGkCkSx4vk6nEWH1MJfReXi2WThvuDRiRpyT7cDoakEcZMQ1iZPgfJgQrcVMR4aJWh6S"},
    {"abandon_eth", kAbandonPhrase, "", "ETH", "m/44'/60'/0'",
     "xpub6DCVMGrdqkJkrRautCvc1Jqpv4hfbyPtSMpZ5KnYDeyggbX3sgFQTT3wjEqF1RtCMazBPhe7gaWYLgEn6qPLhCUddfndnu8Yq6Y3HygJmeu"},
    {"abandon_xrp", kAbandonPhrase, "", "XRP", "m/44'/144'/0'",        
     "xpub6DS7sVJs9bVFkM9UEBHPaA3j4xkzQCFLBhfzxVnKMiRinigBEoaj34wZF2My3XAcP1D3cRhzY6G33fwVYTzCbXoizcBan8qaBj5UwjUihmZ"},
    {"abandon_btc", kAbandonPhrase, passphrase1, "BTC", "m/84'/0'/0'",
     "zpub6qkct9JskdAug8uwucjp7Fs9kT34ykgFqYHYUEDRDPcBg62Ku6tGqFekMdYEXS2K5aR5mFtf5jDA2GDXSa93cNsyLGhTXoDLZnDGgnGKcFp"},
    {"abandon_eth", kAbandonPhrase, passphrase1, "ETH", "m/44'/60'/0'",
     "xpub6CxZrSAPi5CZUJ6ndtyBztgB6nYbegpbRu5r4K7yCDuUmZKiE2d6wtXFHG4WpSx2PgzerWAxrPYXivUkt9vFv4oQoPYBewUQMgXb1mqiWpF"},
    {"abandon_xrp", kAbandonPhrase, passphrase1, "XRP", "m/44'/144'/0'",        
     "xpub6D7x8wgv3pZ5BaSLyvPHKc2jakB1bvnefCu7jVaEZ5D6jg5cJ4ELA1zXsM9w1QdugUZePHFLDP7N4ErHL9AffFDBLfW8ugrw7QVQFWuabP1"},

    {"dice_ones_btc", kDiceOnesPhrase, "", "BTC", "m/84'/0'/0'",
     "zpub6s5dBSKychbfSBoHxL9f5j16tTCrSqhuYgAZnCGuCJiwoKAaC6br8RBcRZa3kAg5TUTiP7SvJ9pB8pSWnCmqpADz5S96kiBhrWA3eJfLe8X"},
    {"dice_ones_eth", kDiceOnesPhrase, "", "ETH", "m/44'/60'/0'",
     "xpub6D5omqcuiHJyDzoaqkv7PhjtBRrLFnHQtUHxafT6stboSDm3wy6n5rRWRWvXuZbbJj81SkAguXWm4t5Cr3zC6AETPbfiuK36hyVzg9dsfet"},
    {"dice_ones_xrp", kDiceOnesPhrase, "", "XRP", "m/44'/144'/0'",
     "xpub6BzaqkYkTSjMmziXw2NcXm6bJWy9cvuQJ7jA8ZPwEASb2zKCeDyse1FNgWsBgKNQK669NnV6Y19TQ551FSuEcZPwFaZdcU5wMghg5CvvMVB"},

    {"dice_ones_btc", kDiceOnesPhrase, passphrase2, "BTC", "m/84'/0'/0'",
     "zpub6rN9Doo3noQZcKqkASmAkcbMqJxvAUiBcW4Smh8azSTqVfgUarDdv3QSFZj8CRrv58GMYEJyKXKiBoz8nT7ZQLnZRPJmwU5Wu9KoYs8S6zu"},
    {"dice_ones_eth", kDiceOnesPhrase, passphrase2, "ETH", "m/44'/60'/0'",
     "xpub6CCL2wvtdoHKwkZxQ2SgM2Md9RKVEQSHWEhy6Gk2osoA3mSkQyjHpHwAajnacAZNEc5jzz23n6RPRvow4a2jmW7qAcDcPZkhtPooaox9d53"},
    {"dice_ones_xrp", kDiceOnesPhrase, passphrase2, "XRP", "m/44'/144'/0'",
     "xpub6C148HkuTmNTAaYHg67q6CKR9mujJmk4TUFWNREHWv8jrwCvHy5ytQqdC9trvGcgboZ7UcdYXEYoWsTvkDUF6J41XyJmuDdghG6ANdqbDGx"}, 
     
    {"random_btc", kRandomPhrase, "", "BTC", "m/84'/0'/0'",
     "zpub6s5dBSKychbfSBoHxL9f5j16tTCrSqhuYgAZnCGuCJiwoKAaC6br8RBcRZa3kAg5TUTiP7SvJ9pB8pSWnCmqpADz5S96kiBhrWA3eJfLe8X"},
};

static const int kAccountXpubVectorCount =
    sizeof(kAccountXpubVectors) / sizeof(kAccountXpubVectors[0]);
