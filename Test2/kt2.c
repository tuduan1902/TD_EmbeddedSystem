<!DOCTYPE html>
<html>
<head>
    <title>MPU6050</title>
    <meta charset="utf-8">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css">
    <style>
        body{ font:14px sans-serif;}
        .wrapper{float:left; width: 500px; padding:20px; margin: 20px}
        .wrapper1{float: left ;margin-left: 500px; margin-top: -413px; width: 70%;  padding:10px}
        .wrapper2{float: left ;margin-left: 500px; margin-top: -213px;  width: 70%;  padding:10px; width: 200%}
        .table_width{margin:auto;margin-top: -413px; width:80%}
        
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.2.0/chart.min.js" ></script> 
</head>
<body>
    <div class="wrapper border border-primary rounded rounded-3">
        <h3 style="color: rgb(255, 77, 6);">MPU 6050 CONTROLLER</h3>
        <h6>Please fill this form to set up MPU6050 Sensor</h6>
        <form action="mpu_setup.php" method="POST">
            <div class="form-group">
                <label><b>Sample Rate</b></label>
                <input type="text" name="sample_rate" class="form-control">
            </div> 
            <br>   
            <div class="form-label">
                <label class="form-label"><b>Digital Low Pass Filter</b> </label>
                     <br>
                    <select aria-label="Default select example" id="DLPF" class="form-select" name="dlpf">
                        <option selected>Choose mode DLPF</option>
                        <option value="260">260 HZ</option>
                        <option value="184">184 HZ</option>
                        <option value="94">94 HZ</option>
                        <option value="44">44 HZ</option>
                        <option value="21">21 HZ</option>
                        <option value="10">10 HZ</option>   
                        <option value="5">5 HZ</option>
                        <option value="3">RESERVED</option>
                    </select>
            </div>
            <br>
            <div class="form-label">
                <label class="form-label"><b>Accelorometer Full Scale</b> </label><br>
                    <div class="form-check form-check-inline">
                        <input class="form-check-label" type="radio" id="Acc1" name="AccFS" value="2">
                        <label class="form-check-label" for=""Acc1>+-2g</label>
                    </div>
                    <div class="form-check form-check-inline">
                        <input class="form-check-label" type="radio" id="Acc2" name="AccFS" value="4">
                        <label class="form-check-label" for=""Acc1>+-4g</label>
                    </div>
                    <div class="form-check form-check-inline">
                        <input class="form-check-label" type="radio" id="Acc3" name="AccFS" value="8">
                        <label class="form-check-label" for=""Acc1>+-8g</label>
                    </div>
                    <div class="form-check form-check-inline">
                        <input class="form-check-label" type="radio" id="Acc4" name="AccFS" value="16">
                        <label class="form-check-label" for=""Acc1>+-16g</label>
            </div>
            <br><br>
            <div class="form-label">
                <label class="form-label"><b>Gyroscope Full Scale</b></label><br>
                <div class="form-check form-check-inline">
                    <input class="form-check-label" type="radio" id="GF1" name="GFS" value="250">
                    <label class="form-check-label" for=""Acc1>+-250</label>
                </div>
                <div class="form-check form-check-inline">
                    <input class="form-check-label" type="radio" id="GF2" name="GFS" value="500">
                    <label class="form-check-label" for=""Acc1>+-500</label>
                </div>
                <div class="form-check form-check-inline">
                    <input class="form-check-label" type="radio" id="GF3" name="GFS" value="1000">
                    <label class="form-check-label" for=""Acc1>+-1000</label>
                </div>
                <div class="form-check form-check-inline">
                    <input class="form-check-label" type="radio" id="GF4" name="GFS" value="2000">
                    <label class="form-check-label" for=""Acc1>+-2000</label>
                </div>
                <br>
                <button type="submit" class="btn btn-primary">Apply</button>
            </div>
        </form>
    </div>

    <div class="wrapper1 border border-primary rounded rounded-3">
            <h5 style="color: rgb(74, 205, 23);"> <b>MPU6050 DATA</b>  </h5>
        <table  class="table table-hover table-striped table_width1" >
            <tr>
                <th scope="col">Roll</th> 
                <td id="td1">  </td>   
            </tr>
            <tr>
                <th scope="col">Pitch</th> 
                <td id="td2">  </td>   
            </tr>
            <tr>
                <th scope="col">Yaw</th> 
                <td id="td3">  </td>   
            </tr>
        </table>
    </div>
    <div class="wrapper2 border border-2 rounded border-primary">
        <bottom>
            <h5 style="color: darkblue;"><b> CHART OF MPU6050 </b></h5>
        </bottom>
        <canvas id="myChart"></canvas>
        <br>
    </div>

    <script>
        /* Set up Char
        */
        var label = [];
        var data1 = [];
        var data2 = [];
        var data3 = [];
        
        const chartdata = {
        labels: label,
            datasets: [{
                label: 'data1',
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: data1
            },
            {
                label: 'data2',
                backgroundColor: 'rgb(99, 255, 132)',
                borderColor: 'rgb(99, 255, 132)',
                data: data2
            },
            {
                label: 'data3',
                backgroundColor: 'rgb(132, 99, 255)',
                borderColor: 'rgb(132, 99, 255)',
                data: data3
            }
        
            ]
        };
        const config = {
            type: 'line',
            data: chartdata,
            options: {
                animation:false
            }
        };
        var myChart = new Chart(
            document.getElementById('myChart'),
            config
        );


        //load data

        $(document).ready(function(){
            update_data();
        });
        setInterval(update_data,1000); // repeat ham updateRGB moi 1s
        function update_data(){
            // gui http request xuong server
            $.post("readData.php",
            function(data){
                var label = [];
                var data1 = [];
                var data2 = [];
                var data3 = [];
                for(var i in data){
                
                // doc gia tri tu server gui len
                var roll = data[i].Ax;
                var pitch = data[i].Ay;
                var yaw = data[i].Az;

                label.push(data[i].id);
                data1.push(data[i].Ax);
                data2.push(data[i].Ay);
                data3.push(data[i].Az);
                
                // gan gia cho cac phan tu
                document.getElementById("td1").innerHTML = roll;
                document.getElementById("td2").innerHTML = pitch;
                document.getElementById("td3").innerHTML = yaw;
                }
                console.log(data);
                myChart.data.labels = label;
                myChart.data.datasets[0].data = data1;
                myChart.data.datasets[1].data = data2;
                myChart.data.datasets[2].data = data3;
                myChart.update();
                
            }) 
        }   
    </script>


</body>
</html>
