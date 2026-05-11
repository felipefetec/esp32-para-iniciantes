# ESP32 para Iniciantes — Códigos do livro

**Autor:** Felipe Tavares  
**Livro:** ESP32 para Iniciantes (distribuição gratuita)

Este repositório contém todos os códigos apresentados no livro, organizados por capítulo. Aqui você encontra tanto os projetos principais quanto as soluções dos desafios.

---

## Como usar este repositório

### Opção 1 — Baixar tudo de uma vez (recomendado para iniciantes)

Clique no botão verde **`<> Code`** no topo desta página e escolha **`Download ZIP`**. Descompacte na pasta que preferir — você terá todos os arquivos organizados por capítulo, prontos para abrir na Arduino IDE.

### Opção 2 — Copiar um arquivo específico

Navegue até a pasta do capítulo desejado, clique no arquivo `.ino` e depois no botão **`Raw`** no canto superior direito. Selecione todo o texto (`Ctrl+A`) e copie para a sua Arduino IDE.

### Opção 3 — Wokwi

Todos os projetos podem ser simulados gratuitamente em [wokwi.com](https://wokwi.com) sem precisar de hardware físico. Cada capítulo do livro tem instruções de montagem no simulador.

---

## Estrutura do repositório

```
esp32-para-iniciantes/
├── capitulo-03-ola-led/
│   ├── blink_serial/             ← projeto do capítulo
│   └── desafio_tres_leds/        ← solução do desafio
├── capitulo-04-entendendo-o-codigo/
│   ├── semaforo/
│   └── desafio_modo_noturno/
├── capitulo-05-eletronica-sem-dor/
│   └── led_externo/
├── capitulo-06-lendo-botoes/
│   ├── botao_toggle/
│   └── desafio_leds_coloridos/
├── capitulo-07-pwm/
│   ├── fade_led/
│   └── desafio_brilho_botao/
└── ... (capítulos 8–12 adicionados conforme o livro avança)
```

---

## Hardware necessário

Para rodar os projetos fisicamente você vai precisar do kit básico descrito no **Apêndice B** do livro:

- ESP32 DevKit v1 (38 ou 30 pinos) + cabo USB
- Protoboard 400 pontos
- LEDs variados + resistores 220Ω e 10kΩ
- Botões push (2–3 unidades)
- Sensor DHT11
- Potenciômetro 10kΩ
- Jumpers macho-macho e macho-fêmea

Não tem o kit ainda? Sem problema — use o [Wokwi](https://wokwi.com) e simule tudo no navegador.

---

## Sobre o livro

**ESP32 para Iniciantes** é um livro técnico gratuito voltado para quem nunca programou e nunca mexeu com eletrônica. Do zero ao projeto final — uma estação climática com WiFi que você acessa pelo celular.

O livro está disponível gratuitamente em PDF. Ao final dele você encontra os links para os outros volumes da série.

---

## Licença

Os códigos deste repositório são disponibilizados para uso educacional.  
Se usar em publicações, vídeos ou outros repositórios, mantenha o cabeçalho de autoria presente em cada arquivo.

© Felipe Tavares
