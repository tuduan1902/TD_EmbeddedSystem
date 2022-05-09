<?php
// Connect to database
$server = "localhost";
$user = "admin";
$password = "123456";
$dbname = "ledControl";

$conn = mysqli_connect($server, $user, $password, $dbname);

// Check connection
if($conn === false) {
   die("ERROR: Could not connect. " . mysqli_connect_error());
}

?>