<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
</head>
<h2>Wine Collection - About</h2>
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
    
    
    <h2>About this website</h2>

<p>This is a website where you can create a profile and store your wine collection and a wine wishlist. </p>

<h3>What to do: </h3>
<p>Sign up by clicking the sign up tab, then enter your information. Next, login by clicking the login tab. Then you can click Add Wine to start your collection! You can also add to a wine wishlist so you can keep track of the wine you would like to buy one day. To view your collections, just click on one of the view tabs.</p>

<a href= "pictures.php">Click here to view a slideshow!</a><br>
<a href= "bbw.php">Click here to play a game!</a>

</html>
