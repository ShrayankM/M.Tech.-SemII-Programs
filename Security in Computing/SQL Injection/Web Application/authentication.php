<?php      
    include('connection.php');  
    ini_set('display_errors', 1);
    $username = $_POST['defaultUsername'];  
    $password = $_POST['defaultPassword'];  
      
        //to prevent from mysqli injection  
        $username = stripcslashes($username);  
        $password = stripcslashes($password);  
        $username = mysqli_real_escape_string($con, $username);  
        $password = mysqli_real_escape_string($con, $password);  
      
        $sql = "SELECT * FROM userAccounts WHERE username = '$username' and password = '$password'";
        echo $sql;
        $result = mysqli_query($con, $sql); 
        
        //echo $result;
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);  
        $count = mysqli_num_rows($result);  
        
        if($count == 1){  
            echo "<h1><center> Login successful </br></br>
                               <h3>User Account Information</h3>
                    </center></h1>"; 
            $account = "SELECT * FROM userInfo WHERE username = '$username'";
            $result = mysqli_query($con, $account);

            while ($row = mysqli_fetch_array($result)) {
                echo "

                <html>
                    <head>
                        <link rel='stylesheet' href = 'login.css'>
                    </head>
                    <body>
                        <table name = 'userInfo' 
                        style = 'border-collapse: collapse;
                        width: 350px; 
                        border-collapse: collapse;
                        border: solid 2px black; 
                        margin:50px auto;'>
                            
                            <tr style = 'border: 1px solid #ccc;
                                         padding: 8px;'>
                                <td style = 'padding: 8px'> Name </td>
                                <td style = 'padding: 8px'>".$row['Name']."</td>
                            </tr>

                            <tr style = 'border: 1px solid #ccc;
                                         padding: 8px;'>
                                <td style = 'padding: 8px'> Account No </td>
                                <td style = 'padding: 8px'>".$row['AccountNo']."</td>
                            </tr>

                            <tr style = 'border: 1px solid #ccc;
                                         padding: 8px;'>
                                <td style = 'padding: 8px'> Balance </td>
                                <td style = 'padding: 8px'>".$row['Balance']."</td>
                            </tr>

                            <tr style = 'border: 1px solid #ccc;
                                         padding: 8px;'>
                                <td style = 'padding: 8px'> Security Code </td>
                                <td style = 'padding: 8px'>".$row['SecurityCode']."</td>
                            </tr>
                        </table>
                    </body>
                </html>
                      ";
            }
            
        }  
        else{  
            echo "<h1> Login failed. Invalid username or password.</h1>";  
        }     
?>  