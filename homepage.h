// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="5">
    <title>Smart Steering Wheel Project</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f8f9fa;
            margin: 20px;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background-color: #ffffff;
            border-radius: 10px;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.1);
            padding: 30px;
            width: 300px;
            text-align: center;
        }

        #sensorData {
            background-color: #f1f1f1;
            border-radius: 10px;
            margin-top: 20px;
            padding: 20px;
        }

        h1 {
            color: #007bff;
        }

        h2 {
            color: #6c757d;
        }

        p {
            margin: 10px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Smart Steering Wheel Project</h1>
<div>
                    <h2 style="color: #007bff;">Current Sensor Data</h2>
                    <p style="margin-bottom: 5px;">Temperature:)=====");String homePagePart2 = F(R"=====( °C</p>
                    <p style="margin-bottom: 5px;">Humidity:)=====");String homePagePart3 = F(R"=====( %</p>
                    <p style="margin-bottom: 5px;">Speed:)=====");String homePagePart4 = F(R"=====( m/s²</p>
                    <p style="margin-bottom: 5px;">BPM:)=====");String homePagePart5 = F(R"=====(</p>
                    <p style="margin-bottom: 5px;">Blood Oxygen:)=====");String homePagePart6 = F(R"=====( %</p>
                </div>
</body>
</html>
)=====");
