#include <M5Atom.h>
#include <stdbool.h>
#include "utility.h"

void setup() {
  M5.begin(true, false, true); // Inicialização M5Atom
  Serial.begin(115200);        // Inicialização do Serial Monitor na velocidade de 115200
  
  // Inicializar botão
  xQueueBotao = xQueueCreate(5, sizeof(info_botao));

  // Criar tarefas
  xTaskCreatePinnedToCore(vTaskLed, "taskLed", 1000, NULL, 0, &taskLed, 0);
  xTaskCreatePinnedToCore(vTaskBotao, "taskBotao", 1000, NULL, 1, &taskBotao, 1);
}

void vTaskBotao(void *pvParameters) {
  info_botao_t info_botao;

  while(true) {
    // Lê informações do botão
    if(M5.Btn.read()){
      vTaskDelay(300 / portTICK_RATE_MS);
      info_botao.value = !info_botao.value;
    } 
    // Manda informação para a fila
    xQueueSend(xQueueBotao, &info_botao, portMAX_DELAY);
  } 
}

void vTaskLed(void *pvParameters){
  info_botao_t info_botao;

  while(true){
    // Recebe informações da fila
    xQueueReceive(xQueueBotao, &info_botao, portMAX_DELAY);
    
    // Processando o valor do botão
    if(info_botao.value == true){
      cor();
      brilho(100);
      Serial.println("Led Ligado\n");
    }
    else {
      Serial.println("Led desligado\n");
      limpar();
    }
  }
}

void loop(){

}