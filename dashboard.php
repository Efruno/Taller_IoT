<!DOCTYPE html>
<html lang="es">
<head>
    <!-- <meta http-equiv="refresh" content="3"> --><!-- Actualiza cada segundo -->
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Temperatura del Invernadero</title>
    <link rel = "stylesheet" type = "text/css" href = "css/dashboard.css"> 
</head>
<body>
    
    <div class="welcome-container">
        <h2>¡Bienvenido!</h2>
        <p>Hola, estimado! Los datos del invernadero son:</p>
        <hr>
        <h3>Temperatura</h3>
        <div id="temperatureGauge"></div>
        <hr>
        <h3>Humedad</h3>
        <div id="humidityGauge"></div>
        <hr>
        <button onclick="logout()">Cerrar Sesión</button>
    </div>

    <script src="js-libs/raphael.min.js"></script>
    <script src="js-libs/justgage.js"></script>
    <script>
        let temperatureGauge = new JustGage({
            id: "temperatureGauge",
            value: 0,
            min: 0,
            max: 50,
            symbol: "°C",
            pointer: true,
            gaugeWidthScale: 0.7,
            counter: true
        });

        let humidityGauge = new JustGage({
            id: "humidityGauge",
            value: 0,
            min: 0,
            max: 100,
            symbol: "%",
            pointer: true,
            gaugeWidthScale: 0.7,
            counter: true
        });

        function actualizarDatos() {
            fetch("actualizaDatos.php") //datos.php
            .then(res => res.json())
            .then(data => {
                temperatureGauge.refresh(data.temperature);
                humidityGauge.refresh(data.humidity);
            });
        }

        setInterval(actualizarDatos, 1000); // Actualiza cada 1000 milisegundos 1s en la pagína web
        window.onload = actualizarDatos;

        function logout() {
            window.location.href = "index.html";
        }
    </script>
</body>
</html>
