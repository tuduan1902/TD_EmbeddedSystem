<?php
    // connect vao server
    include("config.php");

?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>MPU6050</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
    <style>
        body{ font: 14px sans-serif; }
        .wrapper{ width: 350px; padding: 20px; }
    </style>
  </head>
  <body>
    <div class="container">
      <div id="content"></div>


    </div>
  </body>
</html>
<script>
  function loadXMLDoc() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("content").innerHTML =
        this.responseText;
      }
    };
    xhttp.open("GET", "server.php", true);
    xhttp.send();
  }
  setInterval(function(){
    loadXMLDoc();
  },1000)

  window.onload = loadXMLDoc;
</script>