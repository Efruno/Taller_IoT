<?php
$temperature = $_GET['temperature'] ?? null;
$humidity    = $_GET['humidity'] ?? null;

if ($temperature && $humidity) {
    $registro = "Temperature: $temperature °C | Humidity: $humidity %\n";
    file_put_contents("datos.txt", $registro, FILE_APPEND);
    echo "Data saved successfully";
} else {
    echo "Missing parameters";
}
?>