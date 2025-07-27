<?php
// Leer el archivo donde se guardaron los datos
$lineas = file("datos.txt");

// Tomamos la última línea registrada
$ultima = trim(end($lineas));

// Extraer valores usando expresión regular o delimitadores
// Ejemplo si la línea es: "Temperature: 25.3 °C | Humidity: 70.1 %"
preg_match("/Temperature:\s([\d.]+).*Humidity:\s([\d.]+)/", $ultima, $coincidencias);

$temperature = $coincidencias[1] ?? 0;
$humidity    = $coincidencias[2] ?? 0;

// Devolver JSON para el dashboard
echo json_encode([
    "temperature" => floatval($temperature),
    "humidity"    => floatval($humidity)
]);
?>