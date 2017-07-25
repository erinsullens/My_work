<?php
	session_start();
	include 'connect.php';
 
	if ((isset($_POST['userName'])) && (isset($_POST['password'])) ){
		$userName = $_POST['userName'];
		$password = $_POST['password'];
	
		$dbc = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
		if (!$dbc) {
			die('Could not connect: ');
		}
	
		$query = "SELECT * FROM members WHERE userName='$userName' and password='$password'";
		$result = mysqli_query($dbc, $query);
	
		if (mysqli_num_rows($result) == 1) {
	
			// The log-in is OK so set the user ID and username session vars (and cookies), and redirect to the home page
			  $row = mysqli_fetch_array($result);
			  $_SESSION['firstName'] = $row['firstName'];
			  $_SESSION['valid_user'] = $row['userName'];
              $_SESSION['memberId'] = $row['memberId'];
			}
		else {
          // The username/password are incorrect so set an error message
			echo "Sorry, you must enter a valid username and password to log in.";
		}
		mysqli_free_result($result);
		mysqli_close($dbc);
	}  

?>


<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
    <script type = "text/JavaScript" src = "ajax_login.js"> </script>
</head>
<h2>Wine Collection - Login</h2>
    <?php
    if (isset($_SESSION['valid_user'])) {
		echo " You are logged in as: " .$_SESSION['firstName']; 
		echo " <p>  ";
		
	}
    else{
        echo "You are not logged in";
        echo "<p>";
    }
    ?>
 Erin Sullens CS290<br>
<div class= "nav">
<ul>
<li><a href= "home.php">Home</a></li>
    <li><a href= "about.php">About</a></li>

<li><a href= "signup.php">Signup</a></li>
<li><a href= "login.php">Login</a></li>
<li><a href= "addWine.php">Add To Wine Collection</a></li>
<li><a href= "addWishlist.php">Add to Wine Wishlist</a></li>
<li><a href= "view.php">View Collection</a></li>
<li><a href= "viewWL.php">View Wishlist</a></li>
<li><a href= "logout.php">Logout</a></li>
</ul></div>
<div id="left"></div>
<div id="right"></div>
<div id="top"></div>
<div id="bottom"></div>
    
<div id="left2"></div>
<div id="right2"></div>
<div id="top2"></div>
<div id="bottom2"></div>
    
    
<?php

	if (isset($_SESSION['valid_user'])) {
		echo " <h3> You are logged in as </h3><p> User: ".$_SESSION['valid_user']; 
		echo " <p> First Name: ".$_SESSION['firstName'];
		
	}
	else {
		if (isset($userName)) {
			// user tried but can't log in
			echo "<h2> Could not log you in </h2>";
		} else {
			// user has not tried
			echo " <h2> You need to log in </h2> ";
		}
		// Log in form

		echo " <form method='post' action='login.php' > ";
		echo " User name <input type='text' name='userName' onblur = 'checkUserName(this.value)'> <br /> ";
		echo "  Password <input type='password' name='password' /> <br />";
		echo '<input type="submit" value="Log In" name="submit" />';
		echo "</form>";
	}	
?>
    
    

</html>
