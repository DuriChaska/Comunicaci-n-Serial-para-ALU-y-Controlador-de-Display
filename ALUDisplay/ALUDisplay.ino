// Variables para comunicación serial
char data[26];
int number_of_bytes_received;

void setup() { 
  // Configuración inicial
  Serial.begin(9600);
  Serial.println("En línea, esperando instrucciones...");
}

void loop() {
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
      resultado = 5 + 3; // Ejemplo de suma (puedes ajustar los valores)
      break;
    case 2: // División (asegúrate de evitar divisiones por 0)
      if (3 != 0) { // Ejemplo divisor
        resultado = 15 / 3; // Ejemplo de división
      } else {
        Serial.println("Error: División por cero");
        return;
      }
      break;
    default:
      Serial.println("Operación no definida");
      return;
  }

  // Mostrar resultado en serial
  Serial.print("Resultado: ");
  Serial.println(resultado);

  // Aquí agregarías el código para enviar `resultado` al display de 7 segmentos
}
