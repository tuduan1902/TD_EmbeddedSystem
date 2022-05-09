<?php

// Connect to server
include("config.php");

// Create variable
$red = $green = $blue = 0;

// Read value RGB from Database
$sql = "select * from rgbValues";
$result = mysqli_query($conn, $sql);
$rgb = mysqli_fetch_row($result); // rgb[0]-> red; rgb[1]->green,rgb[2]->blue
 
// Assign RGB value to variable
$color = ($rgb[0]<<16)|($rgb[1]<<8)|$rgb[2];

// Read User inputs -> Send to database
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $red = $_POST["r"];
    $green = $_POST["g"];
    $blue = $_POST["b"];

    // Update rgb values
    $sql = "update rgbValues set red=$red,green=$green,blue=$blue, isUpdated=1";
    mysqli_query($conn, $sql);
    // Read value RGB from database
    $sql = "select * from rgbValues";
    $result = mysqli_query($conn, $sql);

    $rgb = mysqli_fetch_row($result); // rgb[0]-> red; rgb[1]->green,rgb[2]->blue

    // Assign RGB value to variable
    $color = ($rgb[0]<<16)|($rgb[1]<<8)|$rgb[2]; //24 bit
}

mysqli_close($conn);

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>LED CONTROL</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
	<style>
        body{ font: 14px sans-serif; }
        .wrapper{ float: left; width: 30%; padding: 20px; margin: 20px; height: 420px; }
		.box{ margin: auto; width: 60%; height: 50%;}
		.table_size{margin: auto; width: 70%;}
    </style>
</head>
<body>
    <div class="wrapper border border-2 rounded border-primary">
        <h3>RGB LED CONTROL </h2>
        <br>
        <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="POST">
            <div class="mb-3">
                <label class="form-label">Brightness</label>
                <input type="range" class="form-range" min="0" max="10" name="brightness" id="brightness">
				<div class="form-text">Scroll the slider to select the LED brightness </div>
			</div>
            <div class="mb-3">
                <label class="form-label">Color Adjustment</label> <br>
                R: <input type="range" class="form-range" name="r" min="0" max="255" id="red" value="<?php echo $rgb[0]; ?>">
				G: <input type="range" class="form-range" name="g" min="0" max="255" id="green" value="<?php echo $rgb[1]; ?>">
				B: <input type="range" class="form-range" name="b" min="0" max="255" id="blue" value="<?php echo $rgb[2]; ?>">

            </div>
            <div class="mb-3">
                <input type="submit" class="btn btn-primary" value="Apply">
            </div>
        </form>
    </div>  
	<div class="wrapper border border-2 rounded border-primary">
        <h3>CURRENT LED COLOR </h2>
        <br>
        <div class="box border border-info" style="background-color: #<?php echo dechex($color); ?>;"> </div> <br>
		<h5> Current RGB values:</h5>
		<table class="table table_size">
			<thead>
				<tr>
					<th scope="col">Red</th>
					<th scope="col">Green</th>
					<th scope="col">Blue</th>
				</tr>
			</thead>
			<tbody>
				<tr>
					<td><?php echo $rgb[0]; ?></td>
					<td><?php echo $rgb[1]; ?></td>
					<td><?php echo $rgb[2]; ?></td>
				</tr>
			</tbody>
		</table>
			
    </div> 	
	
</body>
</html>