<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
</head>
<h2>Wine Collection - Sign Up</h2>
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
    <?php

  require_once('connect.php');
  // Connect to the database
  $dbc = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);

  if (isset($_POST['submit'])) {
    // Grab the profile data from the POST
    $userName = mysqli_real_escape_string($dbc, trim($_POST['userName']));
    $password1 = mysqli_real_escape_string($dbc, trim($_POST['password1']));
    $firstName = mysqli_real_escape_string($dbc, trim($_POST['firstName']));	


    if (!empty($userName) && !empty($password1)) {
      // Make sure someone isn't already registered using this username
      $query = "SELECT * FROM members WHERE userName = '$userName'";
      $data = mysqli_query($dbc, $query);
      if (mysqli_num_rows($data) == 0) {
        // The username is unique, so insert the data into the database
        $query = "INSERT INTO members (userName, password, firstName) VALUES ('$userName', '$password1', '$firstName')";
        mysqli_query($dbc, $query);

        // Confirm success with the user
        echo '<p>Your new account has been successfully created. You\'re now ready to log in.</p>';
          $link = "login.php";
        echo '<a href="'.$link.'">Click here to return to login screen</a>';

        mysqli_close($dbc);
        exit();
      }
      else {
        // An account already exists for this username, so display an error message
        echo '<p class="error">An account already exists for this username. Please use a different address.</p>';
        $username = "";
      }
    }
    else {
      echo '<p class="error">You must enter all of the sign-up data, including the desired password twice.</p>';
    }
  }

  mysqli_close($dbc);
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
<li><a href= "viewWL.php">View Wishlist</a></li><li><a href= "logout.php">Logout</a></li>
</ul></div>
<div id="left"></div>
<div id="right"></div>
<div id="top"></div>
<div id="bottom"></div>
    
<div id="left2"></div>
<div id="right2"></div>
<div id="top2"></div>
<div id="bottom2"></div>
    
 <p>Please enter your username and desired password to sign up for an account.</p>
  <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
    
    
      <label for="username">Username:</label>
      <input type="text" id="userName" name="userName" value="<?php if (!empty($userName)) echo $userName; ?>" /><br />
      <label for="password1">Password:</label>
      <input type="password" id="password1" name="password1" /><br />
      <label for="firstname">First name:</label>
      <input type="text" id="firstName" name="firstName" /><br />      	  
    
    <input type="submit" value="Sign Up" name="submit" />
  </form>
</body>    
</html>
