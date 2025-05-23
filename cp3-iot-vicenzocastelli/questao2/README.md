## Sensor de Gás com ESP32 + Buzzer e LED

Este código demonstra como utilizar o `sensor de gás MQ2` com um ESP32 para detectar a presença de gases inflamáveis ou fumaça. Quando a detecção ocorre, o sistema aciona um LED e um buzzer como alertas.

## Sobre o Sensor MQ2 (Sensor de gás)

O MQ-2 é um sensor de fumaça e gás combustível. Ele pode detectar gases inflamáveis ​​em uma faixa de 300 a 10.000 ppm.

Em resumo: 

- Detecta a presença de Fumaça, Gás butano, propano, metano, Álcool, hidrogênio, entre outros...
- Envia um sinal análogica ou Digital para o arduino. Usamos o sinal digital com 2 estados (HIGH, LOW), que muda para `LOW` se a concentração ultrapassa um limite (pré configurado).

### Funcionamento do Código

O programa:
- Lê o sinal digital do sensor MQ2 (pino 13)
- Se detectar gás/fumaça (LOW):
    - Aciona o LED (pino 2)
    - Ativa o buzzer (pino 18) com PWM
- Se não detectar:
    - Mantém LED e buzzer desligados
- Exibe os status no Serial Monitor

