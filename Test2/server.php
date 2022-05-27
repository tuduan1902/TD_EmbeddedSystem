<?php
  include("config.php");
?>
<center>
  <div class="wrapper">
    <h1>MPU6050</h1>
    <!--<label for="exampleColorInput" class="form-label">Giá trị Ax</label>-->
    <div id="station_data">
    <?php
      // tao bien chua gia tri
      $Ax = $Ay = $Az = 0;
      // doc gia tri rgb tu database
      $sql = "select * from mpu_value";
      $result = mysqli_query($conn, $sql);
      while ($value = mysqli_fetch_row($result))
      {
          $Ax=$value[1];
          $Ay=$value[2];
          $Az=$value[3];
      }
    ?>
      <div class="input-group mb-3">
      <span class="input-group-text" id="inputGroup-sizing-default">Giá trị Ax</span>
      <input type="text" id="Ax_value" class="form-control" aria-label="Sizing example input" aria-describedby="inputGroup-sizing-default" value="<?php echo $Ax; ?>" readonly>
      </div>
      <div class="input-group mb-3">
        <span class="input-group-text" id="inputGroup-sizing-default">Giá trị Ay</span>
        <input type="text" id="Ay_value" class="form-control" aria-label="Sizing example input" aria-describedby="inputGroup-sizing-default" value="<?php echo $Ay; ?>" readonly>
      </div>
      <div class="input-group mb-3">
        <span class="input-group-text" id="inputGroup-sizing-default">Giá trị Az</span>
        <input type="text" id="Az_value" class="form-control" aria-label="Sizing example input" aria-describedby="inputGroup-sizing-default" value="<?php echo $Az; ?>" readonly>
      </div>
    </div>  
  </div>   
</center> 