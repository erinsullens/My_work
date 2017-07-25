<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
</head>
<h2>Wine Collection - Add Wine</h2>
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
    
    $dbc = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
    
    if (isset($_POST['submit'])) {
    // Grab the profile data from the POST
    $winery = mysqli_real_escape_string($dbc, trim($_POST['winery']));
    $wineType = mysqli_real_escape_string($dbc, trim($_POST['wineType']));
    $vintage = mysqli_real_escape_string($dbc, trim($_POST['vintage']));
        $datePurchased = mysqli_real_escape_string($dbc, trim($_POST['datePurchased']));
        $wineColor = mysqli_real_escape_string($dbc, trim($_POST['wineColor']));
        $notes = mysqli_real_escape_string($dbc, trim($_POST['notes']));
    $mId = $_SESSION['memberId'];

   $query = "INSERT INTO wine (winery, wineType, vintage, wineColor, notes, datePurchased, memberId) VALUES ('$winery', '$wineType', '$vintage', '$wineColor', '$notes', '$datePurchased', '$mId')";
        mysqli_query($dbc, $query); 
        
        echo '<p>You have added a wine to your wishlist</p>';
          $link = "addWishlist.php";
        echo '<a href="'.$link.'">Click here to return</a>';
        
        mysqli_close($dbc);
        exit();
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
    
    
    <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
    
    
      <label for="winery">Winery:</label>
      <input type="text" id="winery" name="winery" value="" ><br >
      <label for="wineType">Wine Type:</label>
      <input type="text" id="wineType" name="wineType" ><br >
      <label for="vintage">Vintage:</label>
      <input type="text" id="vintage" name="vintage" ><br >
      <label for="notes">Notes:</label>
      <input type="text" id="notes" name="notes" ><br > 
        
        <label for="datePurchased">Date Purchased:</label>
      <input type="date" id="datePurchased" name="datePurchased" /><br />
        
        
        
    <label for="wineColor">Wine Color:</label>
      <select name="wineColor">
          <option selected="selected">Select a color</option>
        <option value="Red">Red</option>
        <option value="White">White</option>
        <option value="Rose">Rose</option>
        <option value="Other">Other</option>
        </select> 
        <br>
    <input type="submit" value="Submit" name="submit" />
  </form>
    
</html>
