<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
            <script src="slide.js" type = text/javascript></script>

</head>
<h2>Wine Collection - Slideshow</h2>
    <?php
    if (isset($_SESSION['valid_user'])) {
		echo " You are logged in as: " .$_SESSION['memberId']; 
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
    
    <div id="everything">
            <h2>Wine Slideshow</h2>
            <a href= "../assignment3.html">Back</a><br>
    <img id="image" src="images/pic1.png" alt="pic1" height=200>
        <br>
    
    <input type="button" onclick="swapImage()" value="Next">
    <input type="button" onclick="prev()" value="Prev">
    
        </div>
</html>
