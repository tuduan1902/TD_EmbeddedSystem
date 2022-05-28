<?php
// Connect to database
$server = "localhost";
$user = "admin"; 
$pass = "123456";
$dbname = "mpu6050";

$conn = mysqli_connect($server,$user,$pass,$dbname);

// Check connection
if($conn === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}

?>