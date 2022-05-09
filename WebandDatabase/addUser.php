<?php
// Read database from website send
$acc = $_POST['username']; // send by POST proctocol
$pass = $_POST['password'];

// Connect to database
include("config.php");

// Send data to database
// define type is varchar so '$acc' but type is int not ''
$sql = "insert into accounts (user,pass) values ('$acc','$pass')";
mysqli_query($conn, $sql);

// Disconnect the database
mysqli_close($conn);

?>