// Variables para comunicación serial
char data[26];
int number_of_bytes_received;

// Pines de los botones
const int pushButton2 = 2;
const int pushButton3 = 3;
const int pushButton4 = 4;
const int pushButton5 = 5;

// Variables de estado
int buttonState2, buttonState3, buttonState4, buttonState5;

void setup() { 
  // Configuración inicial
  Serial.begin(9600);
  Serial.println("En línea, esperando instrucciones...");
  
  // Configurar pines de botones como entrada
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);
  pinMode(pushButton4, INPUT);
  pinMode(pushButton5, INPUT);
}

void loop() {
  // Leer botones
  buttonState2 = digitalRead(pushButton2);
  buttonState3 = digitalRead(pushButton3);
  buttonState4 = digitalRead(pushButton4);
  buttonState5 = digitalRead(pushButton5);

  // Mostrar estados de los botones en el puerto serial
  Serial.print("Botones: ");
  Serial.print(buttonState2); Serial.print(",");
  Serial.print(buttonState3); Serial.print(",");
  Serial.print(buttonState4); Serial.print(",");
  Serial.println(buttonState5);

  // Procesar datos recibidos por comunicación serial
  if (Serial.available()) {
    number_of_bytes_received = Serial.readBytesUntil(13, data, 25); // Leer hasta 25 bytes o hasta recibir <CR>
    data[number_of_bytes_received] = '\0'; // Agregar terminador nulo

    // Comparar comandos
    if (strcmp(data, "sum") == 0) { 
      Serial.println("Instrucción: Suma");
      realizarOperacion(1); // Código para suma
    } else if (strcmp(data, "di") == 0) { 
      Serial.println("Instrucción: División");
      realizarOperacion(2); // Código para división
    } else {
      Serial.println("Instrucción no reconocida");
    }
  }

  delay(100); // Retraso para estabilidad
}

// Función para realizar operaciones
void realizarOperacion(int operacion) {
  int resultado = 0;

  // Dependiendo de la operación
  switch (operacion) {
    case 1: // Suma
      resultado = buttonState2 + buttonState3 + buttonState4 + buttonState5;
      break;
    case 2: // División (asegúrate de evitar divisiones por 0)
      if (buttonState3 != 0) {
        resultado = buttonState2 / buttonState3;
      } else {
        Serial.println("Error: División por cero");
        return;
      }
      break;
    default:
      Serial.println("Operación no definida");
      return;
  }

  // Mostrar resultado en serial y display (a implementar)
  Serial.print("Resultado: ");
  Serial.println(resultado);

  // Aquí agregarías el código para enviar `resultado` al display de 7 segmentos
}
