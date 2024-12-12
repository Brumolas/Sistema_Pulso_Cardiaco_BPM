int pulso = 0;
int umbral = 515; // Umbral para detectar picos
int conteoLatidos = 0; // Contador de latidos
unsigned long tiempoInicio = 0; // Tiempo inicial del intervalo
unsigned long ultimoPico = 0; // Marca de tiempo del último pico
int intervaloMedicion = 10000; // Intervalo de medición en ms (10 segundos)

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial a 9600 bps
  pinMode(A0, INPUT); // Configura A0 como entrada para leer el sensor
  pinMode(11, OUTPUT); // Configura el pin 11 como salida para el LED
  tiempoInicio = millis(); // Inicializa el tiempo de inicio
}

void loop() {
  pulso = analogRead(A0); // Lee el valor analógico del sensor en A0

  // Detecta un pico si la señal supera el umbral y ha pasado tiempo suficiente desde el último pico
  if (pulso >= umbral && (millis() - ultimoPico > 300)) { // 300 ms como periodo refractario (~200 BPM máx)
    conteoLatidos++; // Incrementa el conteo de latidos
    ultimoPico = millis(); // Actualiza el tiempo del último pico

    // Enciende el LED brevemente como indicador visual
    digitalWrite(11, HIGH);
    delay(30);
    digitalWrite(11, LOW);
  }

  // Cada 10 segundos, calcula los BPM
  if (millis() - tiempoInicio >= intervaloMedicion) {
    int bpm = (conteoLatidos * 60000) / intervaloMedicion; // Escala el conteo a BPM
    Serial.print("Latidos por minuto: ");
    Serial.println(bpm);
    
    // Reinicia el contador y el tiempo
    conteoLatidos = 0;
    tiempoInicio = millis();
  }

  delay(10); // Breve pausa para estabilizar
}