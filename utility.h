#include <M5Atom.h>
#include <stdbool.h>

// Criação das Tarefas
TaskHandle_t taskLed;
TaskHandle_t taskBotao;

// Criar fila para ação do botão
QueueHandle_t xQueueBotao;

typedef struct {
  bool value;
} info_botao_t;

info_botao_t info_botao;

// Define a intensidade do Led
void brilho(int intensidade) {
  M5.dis.setBrightness(intensidade); 
}

// Define a cor do Led
void cor() {
  M5.dis.fillpix(0xFFFF00); // Amarelo
}

// Apaga todos os LEDs acesos
void limpar() {
  M5.dis.clear();  
}


