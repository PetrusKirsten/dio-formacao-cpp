#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Endereço comum do LCD I2C é 0x27 ou 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PIN_TEMP = A0;
const int PIN_UMIDADE = A1;
const int PIN_LAMPADA = 8;
const int PIN_MOTOR = 9;

void setup() {    
    lcd.init();
    lcd.backlight();
    pinMode(PIN_LAMPADA, OUTPUT);
    pinMode(PIN_MOTOR, OUTPUT);
    
    lcd.setCursor(0, 0);
    lcd.print("Sistema Estufa");
    delay(1000);
    lcd.clear();
}

void loop() {
    // --- LEITURA ---
    int leituraTemp = analogRead(PIN_TEMP);
    float temperatura = ((leituraTemp * 5.0 / 1023.0) - 0.5) * 100.0;

    int leituraUmidade = analogRead(PIN_UMIDADE);
    int umidade = map(leituraUmidade, 0, 1023, 0, 100);

    // --- LÓGICA ---
    // Lâmpada (Calor)
    if (temperatura < 37.0) digitalWrite(PIN_LAMPADA, HIGH);
    else digitalWrite(PIN_LAMPADA, LOW);

    // Motor (Umidade/Ventilação)
    if (umidade < 80) digitalWrite(PIN_MOTOR, HIGH);
    else digitalWrite(PIN_MOTOR, LOW);

    // --- EXIBIÇÃO NO LCD ---
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura, 1); // 1 casa decimal
    lcd.print(" oC   "); // Espaços para limpar resíduos

    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%   ");

    delay(1000); 
}