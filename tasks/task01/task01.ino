const uint8_t pins[] = {3, 5, 6, 9, 10};  // Пины
const unsigned long periods[] = {10000, 1000, 500, 100, 50};  // Периоды в мкс

unsigned long previousMicros[5] = {0};  // Последнее переключение каждого пина
uint8_t pinStates = 0b00000000;  // Состояние пинов (битовая маска)

volatile uint8_t *ports[] = {&PORTD, &PORTD, &PORTD, &PORTB, &PORTB};
const uint8_t bitMasks[] = {1 << 3, 1 << 5, 1 << 6, 1 << 1, 1 << 2};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMicros = micros();

  for (int i = 0; i < 5; i++) {
    if (currentMicros - previousMicros[i] >= periods[i]) {
      previousMicros[i] = currentMicros;
      pinStates ^= (1 << i);  // Инвертируем бит состояния

      // Прямая запись в порт
      if (pinStates & (1 << i)) {
        *ports[i] |= bitMasks[i];  // Установить бит (HIGH)
      } else {
        *ports[i] &= ~bitMasks[i];  // Сбросить бит (LOW)
      }
    }
  }
}
