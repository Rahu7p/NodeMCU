<?php

$contador = $_GET['cont'];

echo "El valor de contador es: " .$contador;

$usuario = "root";
$contrasena = "";
$servidor = "localhost";
$basededatos = "testnodemcu";

$conexion = mysqli_connect( $servidor, $usuario, "" ) or die ("No se ha podido conectar al servidor de base de datos");

$db = mysqli_select_db( $conexion, $basededatos ) or die ("No se ha podido seleccionar la base de datos");

$fecha = time();
$consulta = "INSERT INTO datos (fecha, contador) VALUES (".$fecha.", ".$contador.")";

$resultado = mysqli_query( $conexion, $consulta );

?>
