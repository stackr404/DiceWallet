#include "ui/text/ui_text.h"

#include <string.h>

struct UiTextEntry
{
  const char *en;
  const char *fr;
  const char *de;
  const char *pl;
  const char *sv;
  const char *nl;
  const char *ru;
  const char *it;
  const char *zh;
  const char *ja;
  const char *ko;
  const char *es;
  const char *pt;
};

static const UiTextEntry kText[] = {
  {"Back", "Retour", "Zurück", "Wstecz", "Tillbaka", "Terug", "Назад", "Indietro", "返回", "戻る", "뒤로", "Atrás", "Voltar"},
  {"Cancel", "Annuler", "Abbrechen", "Anuluj", "Avbryt", "Annuleren", "Отмена", "Annulla", "取消", "キャンセル", "취소", "Cancelar", "Cancelar"},
  {"Import Wallet", "Importer", "Importieren", "Importuj", "Importera", "Importeren", "Импорт", "Importa", "导入", "インポート", "가져오기", "Importar", "Importar"},
  {"Continue", "Continuer", "Weiter", "Dalej", "Fortsätt", "Verder", "Далее", "Continua", "继续", "続行", "계속", "Continuar", "Continuar"},
  {"Main Menu", "Menu", "Hauptmenü", "Menu", "Huvudmeny", "Hoofdmenu", "Меню", "Menu", "主菜单", "メニュー", "메뉴", "Menú", "Menu"},
  {"Del", "Eff.", "Löschen", "Usuń", "Radera", "Wis", "Удал.", "Canc", "删除", "削除", "삭제", "Borrar", "Apagar"},
  {"OK", "OK", "OK", "OK", "OK", "OK", "ОК", "OK", "确定", "OK", "확인", "OK", "OK"},
  {"Word Index %d of 24", "Index %d/24", "Index %d/24", "Indeks %d/24", "Index %d/24", "Index %d/24", "Индекс %d/24", "Indice %d/24", "索引 %d/24", "索引 %d/24", "인덱스 %d/24", "Índice %d/24", "Índice %d/24"},
  {"Word: %s", "Mot : %s", "Wort: %s", "Słowo: %s", "Ord: %s", "Woord: %s", "Слово: %s", "Parola: %s", "单词：%s", "単語: %s", "단어: %s", "Palabra: %s", "Palavra: %s"},
  {"About", "À propos", "Info", "O programie", "Om", "Info", "О программе", "Info", "关于", "情報", "정보", "Acerca de", "Sobre"},
  {"Advanced", "Avancé", "Erweitert", "Zaawansowane", "Avancerat", "Geavanceerd", "Дополнительно", "Avanzate", "高级", "詳細", "고급", "Avanzado", "Avançado"},
  {"Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)", "Bitcoin (BTC)"},
  {"Enter word index", "Entrez l'index", "Index eingeben", "Podaj indeks", "Ange index", "Voer index in", "Введите индекс", "Inserisci indice", "输入索引", "索引を入力", "인덱스 입력", "Índice de palabra", "Índice da palavra"},
  {"Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)", "Ethereum (ETH)"},
  {"Invalid index", "Index invalide", "Ungültiger Index", "Zły indeks", "Ogiltigt index", "Ongeldige index", "Неверный индекс", "Indice non valido", "无效索引", "無効な索引", "잘못된 인덱스", "Índice no válido", "Índice inválido"},
  {"Language", "Langue", "Sprache", "Język", "Språk", "Taal", "Язык", "Lingua", "语言", "言語", "언어", "Idioma", "Idioma"},
  {"Pre-delivery", "Pré-livraison", "Vor Auslieferung", "Przed wydaniem", "Före leverans", "Voor aflevering", "Перед выдачей", "Pre-consegna", "出厂前", "出荷前", "출고 전", "Preentrega", "Pré-entrega"},
  {"Screen", "Écran", "Bildschirm", "Ekran", "Skärm", "Scherm", "Экран", "Schermo", "屏幕", "画面", "화면", "Pantalla", "Tela"},
  {"Settings", "Réglages", "Einstellungen", "Ustawienia", "Inställningar", "Instellingen", "Настройки", "Impostazioni", "设置", "設定", "설정", "Ajustes", "Ajustes"},
  {"Type the word", "Tapez le mot", "Wort eingeben", "Wpisz słowo", "Skriv ordet", "Typ het woord", "Введите слово", "Scrivi la parola", "输入单词", "単語を入力", "단어 입력", "Escriba la palabra", "Digite a palavra"},
  {"Word 1 of 24", "Mot 1/24", "Wort 1/24", "Słowo 1/24", "Ord 1/24", "Woord 1/24", "Слово 1/24", "Parola 1/24", "单词 1/24", "単語 1/24", "단어 1/24", "Palabra 1/24", "Palavra 1/24"},
  {"XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP", "XRP"},
  {"_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_"},
  {"%s: %d matches. Keep typing.", "%s : %d mots. Continuez.", "%s: %d Treffer. Weiter.", "%s: %d trafień. Pisz dalej.", "%s: %d träffar. Fortsätt.", "%s: %d treffers. Verder.", "%s: %d совпад. Далее.", "%s: %d risultati. Continua.", "%s：%d 个匹配。继续输入。", "%s: %d 件。続けて入力。", "%s: %d개 일치. 계속 입력.", "%s: %d coincidencias. Siga.", "%s: %d resultados. Continue."},
  {"24 BIN Indexes", "24 index BIN", "24 BIN-Indexe", "24 indeksy BIN", "24 BIN-index", "24 BIN-indexen", "24 индекса BIN", "24 indici BIN", "24 个二进制索引", "BIN索引 24", "BIN 인덱스 24", "24 índices BIN", "24 índices BIN"},
  {"24 HEX Indexes", "24 index HEX", "24 HEX-Indexe", "24 indeksy HEX", "24 HEX-index", "24 HEX-indexen", "24 индекса HEX", "24 indici HEX", "24 个十六进制索引", "HEX索引 24", "HEX 인덱스 24", "24 índices HEX", "24 índices HEX"},
  {"24 INT Indexes", "24 index INT", "24 INT-Indexe", "24 indeksy INT", "24 INT-index", "24 INT-indexen", "24 индекса INT", "24 indici INT", "24 个整数索引", "INT索引 24", "INT 인덱스 24", "24 índices INT", "24 índices INT"},
  {"24 Words", "24 mots", "24 Wörter", "24 słowa", "24 ord", "24 woorden", "24 слова", "24 parole", "24 个单词", "24語", "단어 24", "24 palabras", "24 palavras"},
  {"<", "<", "<", "<", "<", "<", "<", "<", "<", "<", "<", "<", "<"},
  {">", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">"},
  {"Amnesic offline dice wallet.", "Portefeuille de dés hors ligne, sans mémoire.", "Offline-Würfel-Wallet ohne Speicher.", "Portfel kostkowy offline, bez pamięci.", "Offline tärningsplånbok utan minne.", "Offline dobbelwallet zonder geheugen.", "Офлайн-кошелёк на костях, без памяти.", "Wallet dadi offline, senza memoria.", "无记忆的离线骰子钱包。", "記憶しないオフラインのサイコロ財布。", "기억하지 않는 오프라인 주사위 지갑.", "Monedero de dados offline, sin memoria.", "Carteira de dados offline, sem memória."},
  {"Autocorrelation", "Autocorrélation", "Autokorrelation", "Autokorelacja", "Autokorrelation", "Autocorrelatie", "Автокорреляция", "Autocorrelazione", "自相关", "自己相関", "자기상관", "Autocorrelación", "Autocorrelação"},
  {"Brightness", "Luminosité", "Helligkeit", "Jasność", "Ljusstyrka", "Helderheid", "Яркость", "Luminosità", "亮度", "明るさ", "밝기", "Brillo", "Brilho"},
  {"Chi-square", "Khi-deux", "Chi-Quadrat", "Chi-kwadrat", "Chi-två", "Chi-kwadraat", "Хи-квадрат", "Chi-quadro", "卡方", "カイ二乗", "카이제곱", "Chi-cuadrado", "Qui-quadrado"},
  {"Choose a word", "Choisir un mot", "Wort wählen", "Wybierz słowo", "Välj ett ord", "Kies een woord", "Выберите слово", "Scegli una parola", "选择单词", "単語を選択", "단어 선택", "Elija una palabra", "Escolha uma palavra"},
  {"Confirm word %d of 24", "Confirmer mot %d/24", "Wort %d/24 bestätigen", "Potwierdź słowo %d/24", "Bekräfta ord %d/24", "Bevestig woord %d/24", "Слово %d/24", "Conferma parola %d/24", "确认单词 %d/24", "単語 %d/24 を確認", "단어 %d/24 확인", "Confirmar palabra %d/24", "Confirmar palavra %d/24"},
  {"Device Secured", "Appareil sécurisé", "Gerät gesichert", "Urządzenie zabezpieczone", "Enhet säkrad", "Apparaat beveiligd", "Устройство защищено", "Dispositivo protetto", "设备已保护", "デバイス保護済み", "기기 보호됨", "Dispositivo protegido", "Dispositivo protegido"},
  {"Secure Boot On", "Démarrage sécurisé activé", "Secure Boot an", "Bezpieczny rozruch włączony", "Säker start på", "Beveiligd opstarten aan", "Безопасная загрузка включена", "Avvio sicuro attivo", "安全启动已开启", "セキュアブート有効", "보안 부팅 켜짐", "Arranque seguro activado", "Inicialização segura ativada"},
  {"Secure Boot Off", "Démarrage sécurisé désactivé", "Secure Boot aus", "Bezpieczny rozruch wyłączony", "Säker start av", "Beveiligd opstarten uit", "Безопасная загрузка выключена", "Avvio sicuro disattivo", "安全启动已关闭", "セキュアブート無効", "보안 부팅 꺼짐", "Arranque seguro desactivado", "Inicialização segura desativada"},
  {"Secure boot is enabled. Only signed firmware will run.", "Démarrage sécurisé actif. Seul un firmware signé démarre.", "Secure Boot ist aktiv. Nur signierte Firmware startet.", "Bezpieczny rozruch włączony. Uruchomi się tylko podpisane oprogramowanie.", "Säker start är på. Endast signerad firmware startar.", "Beveiligd opstarten staat aan. Alleen ondertekende firmware start.", "Безопасная загрузка включена. Запустится только подписанная прошивка.", "Avvio sicuro attivo. Si avvia solo firmware firmato.", "安全启动已开启。仅签名固件可运行。", "セキュアブートが有効です。署名済みファームウェアのみ起動します。", "보안 부팅이 켜져 있습니다. 서명된 펌웨어만 실행됩니다.", "Arranque seguro activado. Solo arranca firmware firmado.", "Inicialização segura ativada. Só corre firmware assinado."},
  {"Secure boot is off. Unsigned firmware can run.", "Démarrage sécurisé inactif. Un firmware non signé peut démarrer.", "Secure Boot ist aus. Unsignierte Firmware kann starten.", "Bezpieczny rozruch wyłączony. Może uruchomić się niepodpisane oprogramowanie.", "Säker start är av. Osignerad firmware kan starta.", "Beveiligd opstarten staat uit. Ongetekende firmware kan starten.", "Безопасная загрузка выключена. Может запуститься неподписанная прошивка.", "Avvio sicuro disattivo. Può avviarsi firmware non firmato.", "安全启动已关闭。未签名固件可以运行。", "セキュアブートは無効です。未署名のファームウェアも起動できます。", "보안 부팅이 꺼져 있습니다. 서명되지 않은 펌웨어도 실행됩니다.", "Arranque seguro desactivado. Puede arrancar firmware sin firmar.", "Inicialização segura desativada. Firmware não assinado pode correr."},
  {"Dice Fairness Tests", "Tests des dés", "Würfeltests", "Testy kości", "Tärningstester", "Dobbeltests", "Тесты костей", "Test dei dadi", "骰子公平性测试", "サイコロ公平性テスト", "주사위 공정성 테스트", "Pruebas de dados", "Testes dos dados"},
  {"Dice Roll %d of %d", "Lancer %d/%d", "Wurf %d/%d", "Rzut %d/%d", "Kast %d/%d", "Worp %d/%d", "Бросок %d/%d", "Lancio %d/%d", "投掷 %d/%d", "サイコロ %d/%d", "주사위 %d/%d", "Tirada %d/%d", "Rolagem %d/%d"},
  {"Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet", "Dice Wallet"},
  {"Dice rolls, seed indexes, and passphrase have been wiped from this device.", "Lancers, index et phrase secrète ont été effacés.", "Würfe, Indexe und Passphrase wurden gelöscht.", "Rzuty, indeksy i hasło zostały wyczyszczone.", "Kast, index och lösenord har raderats.", "Worpen, indexen en wachtwoordzin zijn gewist.", "Броски, индексы и парольная фраза стёрты.", "Lanci, indici e passphrase sono stati cancellati.", "骰子、种子索引和密码短语已从本设备擦除。", "サイコロ、シード索引、パスフレーズを消去しました。", "주사위, 시드 인덱스, 암호 문구가 삭제되었습니다.", "Tiradas, índices y frase secreta borrados.", "Rolagens, índices e frase secreta apagados."},
  {"Die Rolls", "Lancers", "Würfe", "Rzuty", "Kast", "Worpen", "Броски", "Lanci", "投掷", "出目", "주사위", "Tiradas", "Rolagens"},
  {"Die rolls: %d", "Lancers : %d", "Würfe: %d", "Rzuty: %d", "Kast: %d", "Worpen: %d", "Бросков: %d", "Lanci: %d", "投掷次数：%d", "サイコロ回数: %d", "주사위 횟수: %d", "Tiradas: %d", "Rolagens: %d"},
  {"Enter all bits", "Tous les bits", "Alle Bits", "Wszystkie bity", "Alla bitar", "Alle bits", "Все биты", "Tutti i bit", "输入全部位", "全ビット入力", "모든 비트 입력", "Todos los bits", "Todos os bits"},
  {"Entropy is from your dice rolls, not a random number generator.", "L'entropie vient de vos dés, pas d'un générateur.", "Entropie aus Würfen, nicht aus einem Generator.", "Entropia z rzutów, nie z generatora.", "Entropi från kast, inte en generator.", "Entropie uit worpen, niet een generator.", "Энтропия из бросков, не из генератора.", "Entropia dai lanci, non da un generatore.", "熵来自骰子，不是随机数生成器。", "エントロピーはサイコロから。乱数ではない。", "엔트로피는 주사위에서 나옵니다.", "Entropía de sus tiradas, no de un generador.", "Entropia das rolagens, não de um gerador."},
  {"Error", "Erreur", "Fehler", "Błąd", "Fel", "Fout", "Ошибка", "Errore", "错误", "エラー", "오류", "Error", "Erro"},
  {"Exit", "Quitter", "Beenden", "Wyjdź", "Avsluta", "Afsluiten", "Выход", "Esci", "退出", "終了", "종료", "Salir", "Sair"},
  {"Fail", "Échec", "Fehler", "Błąd", "Fel", "Mislukt", "Ошибка", "Fallito", "失败", "失敗", "실패", "Fallo", "Falha"},
  {"Finish", "Terminer", "Fertig", "Koniec", "Klar", "Klaar", "Готово", "Fine", "完成", "完了", "완료", "Fin", "Concluir"},
  {"Flip", "Inverser", "Umschalten", "Odwróć", "Växla", "Wissel", "Сменить", "Inverti", "翻转", "反転", "뒤집기", "Invertir", "Inverter"},
  {"Gap", "Écart", "Lücke", "Przerwa", "Lucka", "Gat", "Интервал", "Intervallo", "间隔", "間隔", "간격", "Hueco", "Intervalo"},
  {"Go to settings / pre-delivery to secure this device.", "Réglages / pré-livraison pour sécuriser.", "Einstellungen / Vor Auslieferung zum Sichern.", "Ustawienia / przed wydaniem, aby zabezpieczyć.", "Inställningar / före leverans för att säkra.", "Instellingen / voor aflevering om te beveiligen.", "Настройки / перед выдачей, чтобы защитить.", "Impostazioni / pre-consegna per proteggere.", "到设置 / 出厂前以保护此设备。", "設定 / 出荷前で保護してください。", "설정 / 출고 전에서 보호하세요.", "Ajustes / preentrega para proteger.", "Ajustes / pré-entrega para proteger."},
  {"If this image changes, the firmware has changed.", "Si l'image change, le firmware a changé.", "Ändert sich das Bild, hat sich die Firmware geändert.", "Jeśli obraz się zmieni, firmware się zmienił.", "Om bilden ändras har firmware ändrats.", "Als het beeld wijzigt, is de firmware gewijzigd.", "Если рисунок изменился, прошивка изменилась.", "Se l'immagine cambia, il firmware è cambiato.", "如果此图变化，固件已改变。", "この画像が変わればファームウェアが変わっています。", "이미지가 바뀌면 펌웨어가 바뀐 것입니다.", "Si la imagen cambia, el firmware cambió.", "Se a imagem mudar, o firmware mudou."},
  {"Import Method", "Méthode", "Importmethode", "Metoda importu", "Importmetod", "Importmethode", "Способ импорта", "Metodo import", "导入方式", "インポート方法", "가져오기 방법", "Método", "Método"},
  {"Instructions", "Instructions", "Anleitung", "Instrukcje", "Instruktioner", "Instructies", "Инструкция", "Istruzioni", "说明", "手順", "안내", "Instrucciones", "Instruções"},
  {"Keep the exact order shown.", "Gardez l'ordre affiché.", "Gezeigte Reihenfolge behalten.", "Zachowaj kolejność.", "Behåll ordningen.", "Houd de volgorde aan.", "Сохраните порядок.", "Mantieni l'ordine.", "请保持所示顺序。", "表示された順序を守ってください。", "표시된 순서를 지키세요.", "Mantenga el orden.", "Mantenha a ordem."},
  {"Longest run", "Plus longue série", "Längste Folge", "Najdłuższa seria", "Längsta följd", "Langste reeks", "Длинная серия", "Serie più lunga", "最长游程", "最長ラン", "최장 연속", "Racha más larga", "Série mais longa"},
  {"Mistakes %d of %d", "Erreurs %d/%d", "Fehler %d/%d", "Błędy %d/%d", "Fel %d/%d", "Fouten %d/%d", "Ошибки %d/%d", "Errori %d/%d", "错误 %d/%d", "誤り %d/%d", "오류 %d/%d", "Errores %d/%d", "Erros %d/%d"},
  {"Mistakes 0 of 3", "Erreurs 0/3", "Fehler 0/3", "Błędy 0/3", "Fel 0/3", "Fouten 0/3", "Ошибки 0/3", "Errori 0/3", "错误 0/3", "誤り 0/3", "오류 0/3", "Errores 0/3", "Erros 0/3"},
  {"Never digitalize (no screenshots/typing).", "Ne pas numériser (pas de capture ni saisie).", "Nicht digitalisieren (kein Foto, kein Abtippen).", "Nie cyfryzuj (bez zdjęć i przepisywania).", "Digitalisera inte (ingen bild, ingen inmatning).", "Niet digitaliseren (geen foto, niet overtypen).", "Не копируйте (без фото и набора).", "Non digitalizzare (niente foto o digitazione).", "不要数字化（不要截图或键入）。", "デジタル化しない（撮影・入力禁止）。", "디지털화하지 마세요(캡처·입력 금지).", "No lo digitalice (sin fotos ni tecleo).", "Não digitalize (sem fotos nem digitação)."},
  {"Never share with anyone.", "Ne partagez avec personne.", "Mit niemandem teilen.", "Nie udostępniaj nikomu.", "Dela inte med någon.", "Deel met niemand.", "Никому не сообщайте.", "Non condividere con nessuno.", "不要告诉任何人。", "誰にも共有しない。", "누구에게도 공유하지 마세요.", "No lo comparta.", "Não compartilhe."},
  {"New Wallet", "Nouveau wallet", "Neues Wallet", "Nowy portfel", "Ny plånbok", "Nieuwe wallet", "Новый кошелёк", "Nuovo wallet", "新建钱包", "新しいウォレット", "새 지갑", "Nuevo monedero", "Nova carteira"},
  {"No matches.", "Aucun mot.", "Keine Treffer.", "Brak trafień.", "Inga träffar.", "Geen treffers.", "Нет совпадений.", "Nessun risultato.", "无匹配。", "一致なし。", "일치 없음.", "Sin coincidencias.", "Nenhum resultado."},
  {"No open security fuses", "Aucun fusible ouvert", "Keine offenen Sicherungen", "Brak otwartych bezpieczników", "Inga öppna säkringar", "Geen open zekeringen", "Нет открытых предохранителей", "Nessun fusibile aperto", "无未熔断保险丝", "未焼きのヒューズなし", "열린 퓨즈 없음", "Sin fusibles abiertos", "Sem fusíveis abertos."},
  {"No seed is stored after use.", "Aucun seed après usage.", "Kein Seed nach Nutzung.", "Seed nie jest zapisany.", "Inget seed sparas.", "Geen seed na gebruik.", "Сид не сохраняется.", "Nessun seed dopo l'uso.", "使用后不保存种子。", "使用後シードは保存されません。", "사용 후 시드는 저장되지 않습니다.", "No se guarda el seed.", "O seed não fica salvo."},
  {"Pass", "Réussi", "Bestanden", "Zaliczony", "Godkänd", "Geslaagd", "ОК", "Superato", "通过", "合格", "통과", "Aprobado", "Aprovado"},
  {"Passphrase", "Phrase secrète", "Passphrase", "Hasło", "Lösenord", "Wachtwoordzin", "Парольная фраза", "Passphrase", "密码短语", "パスフレーズ", "암호 문구", "Frase secreta", "Frase secreta"},
  {"Please power off device", "Éteignez l'appareil", "Gerät ausschalten", "Wyłącz urządzenie", "Stäng av enheten", "Schakel het apparaat uit", "Выключите устройство", "Spegni il dispositivo", "请关闭设备", "電源を切ってください", "기기의 전원을 끄세요", "Apague el dispositivo", "Desligue o dispositivo"},
  {"Poker", "Poker", "Poker", "Poker", "Poker", "Poker", "Покер", "Poker", "扑克", "ポーカー", "포커", "Póker", "Pôquer"},
  {"Proceed", "Continuer", "Weiter", "Dalej", "Fortsätt", "Verder", "Далее", "Procedi", "继续", "進む", "진행", "Continuar", "Prosseguir"},
  {"Public Keys", "Clés publiques", "Öffentliche Schlüssel", "Klucze publiczne", "Publika nycklar", "Publieke sleutels", "Публичные ключи", "Chiavi pubbliche", "公钥", "公開鍵", "공개 키", "Claves públicas", "Chaves públicas"},
  {"Runs", "Séries", "Folgen", "Serie", "Följder", "Reeksen", "Серии", "Sequenze", "游程", "ラン", "런", "Rachas", "Sequências"},
  {"Screen off after %d sec", "Écran off : %d s", "Aus nach %d s", "Wyłącz po %d s", "Av efter %d s", "Uit na %d s", "Экран: %d с", "Spento dopo %d s", "%d 秒后关屏", "%d秒後に消灯", "%d초 후 화면 꺼짐", "Apagado: %d s", "Desliga: %d s"},
  {"Screen off: never", "Écran : jamais", "Aus: nie", "Wyłącz: nigdy", "Av: aldrig", "Uit: nooit", "Экран: никогда", "Spento: mai", "关屏：永不", "消灯: しない", "화면 꺼짐: 안 함", "Apagado: nunca", "Desliga: nunca"},
  {"Secret Recovery Phrase", "Phrase secrète", "Recovery-Phrase", "Fraza odzyskiwania", "Återhämtningsfras", "Herstelzin", "Секретная фраза", "Frase di recupero", "秘密恢复短语", "シークレットフレーズ", "비밀 복구 구문", "Frase de recuperación", "Frase de recuperação"},
  {"Secure Device", "Sécuriser", "Sichern", "Zabezpiecz", "Säkra", "Beveiligen", "Защитить", "Proteggi", "保护设备", "保護する", "보호", "Proteger", "Proteger"},
  {"Secure Wipe", "Effacement", "Sicheres Löschen", "Bezpieczne czyszczenie", "Säker radering", "Veilig wissen", "Очистка", "Cancellazione", "安全擦除", "安全消去", "보안 삭제", "Borrado seguro", "Apagar seguro"},
  {"Secured", "Sécurisé", "Gesichert", "Zabezpieczone", "Säkrad", "Beveiligd", "Защищено", "Protetto", "已保护", "保護済み", "보호됨", "Protegido", "Protegido"},
  {"Select", "Choisir", "Wählen", "Wybierz", "Välj", "Kies", "Выбрать", "Scegli", "选择", "選択", "선택", "Elegir", "Escolher"},
  {"Select Word", "Choisir mot", "Wort wählen", "Wybierz słowo", "Välj ord", "Kies woord", "Выбор слова", "Scegli parola", "选择单词", "単語を選択", "단어 선택", "Elegir palabra", "Escolher palavra"},
  {"Serial", "Série", "Serie", "Szereg", "Serie", "Serie", "Серия", "Serie", "序列", "系列", "연속", "Serie", "Série"},
  {"Show Seed Phrase", "Voir la phrase", "Phrase zeigen", "Pokaż frazę", "Visa fras", "Toon zin", "Показать фразу", "Mostra frase", "显示助记词", "フレーズを表示", "구문 표시", "Ver frase", "Ver frase"},
  {"Start Again", "Recommencer", "Neu starten", "Od nowa", "Börja om", "Opnieuw", "Заново", "Ricomincia", "重新开始", "最初から", "다시 시작", "Empezar de nuevo", "Começar de novo"},
  {"Store offline in a secure place.", "Gardez hors ligne, en lieu sûr.", "Offline sicher aufbewahren.", "Trzymaj offline, w bezpiecznym miejscu.", "Förvara offline, säkert.", "Offline veilig bewaren.", "Храните офлайн в надёжном месте.", "Conserva offline, al sicuro.", "离线存放在安全处。", "オフラインで安全に保管。", "오프라인의 안전한 곳에 보관.", "Guarde offline, en lugar seguro.", "Guarde offline, em local seguro."},
  {"Success", "Succès", "Erfolg", "Sukces", "Klart", "Gelukt", "Готово", "Riuscito", "成功", "成功", "성공", "Correcto", "Sucesso"},
  {"This device is permanently secured using internal hardware locks.", "Appareil verrouillé par le matériel.", "Gerät dauerhaft per Hardware gesperrt.", "Urządzenie trwale zablokowane sprzętowo.", "Enheten är låst med hårdvara.", "Apparaat permanent hardwarematig vergrendeld.", "Устройство заблокировано аппаратно.", "Dispositivo bloccato in hardware.", "设备已由硬件锁永久保护。", "ハードウェアで恒久的に保護されています。", "하드웨어 잠금으로 영구 보호됨.", "Dispositivo bloqueado por hardware.", "Dispositivo bloqueado por hardware."},
  {"Unsecured Device!", "Appareil non sécurisé !", "Ungesichertes Gerät!", "Urządzenie niezabezpieczone!", "Osäkrad enhet!", "Onbeveiligd apparaat!", "Устройство не защищено!", "Dispositivo non protetto!", "设备未保护！", "未保護のデバイス！", "보호되지 않은 기기!", "¡Dispositivo no protegido!", "Dispositivo não protegido!"},
  {"View Seed", "Voir seed", "Seed zeigen", "Pokaż seed", "Visa seed", "Seed bekijken", "Показать сид", "Vedi seed", "查看种子", "シードを表示", "시드 보기", "Ver seed", "Ver seed"},
  {"Wallet mode: Advanced", "Mode : avancé", "Modus: erweitert", "Tryb: zaawansowany", "Läge: avancerat", "Modus: geavanceerd", "Режим: расширенный", "Modo: avanzata", "钱包模式：高级", "モード: 詳細", "지갑 모드: 고급", "Modo: avanzado", "Modo: avançado"},
  {"Wallet mode: Simple", "Mode : simple", "Modus: einfach", "Tryb: prosty", "Läge: enkelt", "Modus: eenvoudig", "Режим: простой", "Modo: semplice", "钱包模式：简单", "モード: シンプル", "지갑 모드: 간단", "Modo: simple", "Modo: simples"},
  {"Warning", "Attention", "Warnung", "Ostrzeżenie", "Varning", "Waarschuwing", "Внимание", "Avviso", "警告", "警告", "경고", "Aviso", "Aviso"},
  {"Wipe device after %d minutes", "Effacer après %d min", "Löschen nach %d Min.", "Wyczyść po %d min", "Radera efter %d min", "Wissen na %d min", "Очистка через %d мин", "Cancella dopo %d min", "%d 分钟后擦除", "%d分後に消去", "%d분 후 삭제", "Borrar tras %d min", "Apagar após %d min"},
  {"Wipe device after 1 minute", "Effacer après 1 min", "Löschen nach 1 Min.", "Wyczyść po 1 min", "Radera efter 1 min", "Wissen na 1 min", "Очистка через 1 мин", "Cancella dopo 1 min", "1 分钟后擦除", "1分後に消去", "1분 후 삭제", "Borrar tras 1 min", "Apagar após 1 min"},
  {"Wipe device: never", "Effacer : jamais", "Löschen: nie", "Czyszczenie: nigdy", "Radera: aldrig", "Wissen: nooit", "Очистка: никогда", "Cancella: mai", "擦除：永不", "消去: しない", "삭제: 안 함", "Borrar: nunca", "Apagar: nunca"},
  {"Word %d of 24", "Mot %d/24", "Wort %d/24", "Słowo %d/24", "Ord %d/24", "Woord %d/24", "Слово %d/24", "Parola %d/24", "单词 %d/24", "単語 %d/24", "단어 %d/24", "Palabra %d/24", "Palavra %d/24"},
  {"Word %d of 24: %s", "Mot %d/24 : %s", "Wort %d/24: %s", "Słowo %d/24: %s", "Ord %d/24: %s", "Woord %d/24: %s", "Слово %d/24: %s", "Parola %d/24: %s", "单词 %d/24：%s", "単語 %d/24: %s", "단어 %d/24: %s", "Palabra %d/24: %s", "Palavra %d/24: %s"},
  {"Works fully offline.", "Entièrement hors ligne.", "Vollständig offline.", "W pełni offline.", "Helt offline.", "Volledig offline.", "Полностью офлайн.", "Completamente offline.", "完全离线工作。", "完全にオフライン。", "완전히 오프라인.", "Totalmente offline.", "Totalmente offline."},
  {"Write down all 24 words.", "Notez les 24 mots.", "Alle 24 Wörter aufschreiben.", "Zapisz 24 słowa.", "Skriv ner 24 ord.", "Schrijf 24 woorden op.", "Запишите все 24 слова.", "Scrivi le 24 parole.", "写下全部 24 个单词。", "24語をすべて書いてください。", "24개 단어를 모두 적으세요.", "Anote las 24 palabras.", "Anote as 24 palavras."},
  {"https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org", "https://dicewallet.org"},
  {"English", "Anglais", "Englisch", "Angielski", "Engelska", "Engels", "Английский", "Inglese", "英语", "英語", "영어", "Inglés", "Inglês"},
  {"French", "Français", "Französisch", "Francuski", "Franska", "Frans", "Французский", "Francese", "法语", "フランス語", "프랑스어", "Francés", "Francês"},
  {"German", "Allemand", "Deutsch", "Niemiecki", "Tyska", "Duits", "Немецкий", "Tedesco", "德语", "ドイツ語", "독일어", "Alemán", "Alemão"},
  {"Polish", "Polonais", "Polnisch", "Polski", "Polska", "Pools", "Польский", "Polacco", "波兰语", "ポーランド語", "폴란드어", "Polaco", "Polonês"},
  {"Swedish", "Suédois", "Schwedisch", "Szwedzki", "Svenska", "Zweeds", "Шведский", "Svedese", "瑞典语", "スウェーデン語", "스웨덴어", "Sueco", "Sueco"},
  {"Dutch", "Néerlandais", "Niederländisch", "Holenderski", "Nederlands", "Nederlands", "Нидерландский", "Olandese", "荷兰语", "オランダ語", "네덜란드어", "Neerlandés", "Holandês"},
  {"Russian", "Russe", "Russisch", "Rosyjski", "Ryska", "Russisch", "Русский", "Russo", "俄语", "ロシア語", "러시아어", "Ruso", "Russo"},
  {"Italian", "Italien", "Italienisch", "Włoski", "Italienska", "Italiaans", "Итальянский", "Italiano", "意大利语", "イタリア語", "이탈리아어", "Italiano", "Italiano"},
  {"Chinese", "Chinois", "Chinesisch", "Chiński", "Kinesiska", "Chinees", "Китайский", "Cinese", "中文", "中国語", "중국어", "Chino", "Chinês"},
  {"Japanese", "Japonais", "Japanisch", "Japoński", "Japanska", "Japans", "Японский", "Giapponese", "日语", "日本語", "일본어", "Japonés", "Japonês"},
  {"Korean", "Coréen", "Koreanisch", "Koreański", "Koreanska", "Koreaans", "Корейский", "Coreano", "韩语", "韓国語", "한국어", "Coreano", "Coreano"},
  {"Spanish", "Espagnol", "Spanisch", "Hiszpański", "Spanska", "Spaans", "Испанский", "Spagnolo", "西班牙语", "スペイン語", "스페인어", "Español", "Espanhol"},
  {"Portuguese", "Portugais", "Portugiesisch", "Portugalski", "Portugisiska", "Portugees", "Португальский", "Portoghese", "葡萄牙语", "ポルトガル語", "포르투갈어", "Portugués", "Português"},
  {"Select 24th Word", "Choisir le 24e mot", "24. Wort wählen", "Wybierz 24. słowo", "Välj 24:e ordet", "Kies 24e woord", "Выбрать 24-е слово", "Scegli la 24a parola", "选择第24个单词", "24番目の単語を選択", "24번째 단어 선택", "Elegir la 24.ª palabra", "Escolher a 24.ª palavra"},
  {"Incorrect 24th index", "24e index incorrect", "24. Index falsch", "Nieprawidłowy 24. indeks", "Felaktigt 24:e index", "Onjuiste 24e index", "Неверный 24-й индекс", "24° indice errato", "第24个索引不正确", "24番目の索引が不正", "24번째 인덱스 오류", "Índice 24 incorrecto", "24.º índice incorreto"},
  {"Skip", "Passer", "Überspringen", "Pomiń", "Hoppa över", "Overslaan", "Пропустить", "Salta", "跳过", "スキップ", "건너뛰기", "Omitir", "Ignorar"},
  {"Empty for none", "Vide pour aucun", "Leer für keines", "Puste oznacza brak", "Tomt för inget", "Leeg voor geen", "Пусто — значит нет", "Vuoto per nessuno", "留空表示无", "空ならなし", "비우면 없음", "Vacío para ninguno", "Vazio para nenhum"},
};

static ui_language s_language = UI_LANG_EN;

void ui_text_set_language(ui_language language)
{
  s_language = language;
}

const char *ui_text_translate(const char *english)
{
  if (english == nullptr || s_language == UI_LANG_EN)
    return english;
  for (unsigned i = 0; i < sizeof(kText) / sizeof(kText[0]); i++)
  {
    if (strcmp(kText[i].en, english) != 0)
      continue;
    const char *t = nullptr;
    switch (s_language)
    {
    case UI_LANG_FR:
      t = kText[i].fr;
      break;
    case UI_LANG_DE:
      t = kText[i].de;
      break;
    case UI_LANG_PL:
      t = kText[i].pl;
      break;
    case UI_LANG_SV:
      t = kText[i].sv;
      break;
    case UI_LANG_NL:
      t = kText[i].nl;
      break;
    case UI_LANG_RU:
      t = kText[i].ru;
      break;
    case UI_LANG_IT:
      t = kText[i].it;
      break;
    case UI_LANG_ZH:
      t = kText[i].zh;
      break;
    case UI_LANG_JA:
      t = kText[i].ja;
      break;
    case UI_LANG_KO:
      t = kText[i].ko;
      break;
    case UI_LANG_ES:
      t = kText[i].es;
      break;
    case UI_LANG_PT:
      t = kText[i].pt;
      break;
    default:
      break;
    }
    return (t != nullptr && t[0] != '\0') ? t : english;
  }
  return english;
}

const lv_font_t *ui_font_for(int size)
{
  if (s_language == UI_LANG_RU)
    return &custom_cyrillic_14;
  if (s_language == UI_LANG_ZH)
    return &custom_zh_16;
  if (s_language == UI_LANG_JA)
    return &custom_ja_16;
  if (s_language == UI_LANG_KO)
    return &custom_ko_16;      
  if (s_language == UI_LANG_FR || s_language == UI_LANG_DE || s_language == UI_LANG_PL || s_language == UI_LANG_SV || s_language == UI_LANG_NL ||s_language == UI_LANG_ES || s_language == UI_LANG_PT) {
    return &custom_eu_16;
  }
  if (size >= 22)
    return &lv_font_montserrat_22;
  if (size >= 18)
    return &lv_font_montserrat_18;
  return &lv_font_montserrat_14;
}