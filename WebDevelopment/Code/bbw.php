<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
    <script src="bbw.js" type = text/javascript>


</script>
</head>
<h2>Wine Collection - Game</h2>
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
    
    
    <h2>Welcome to Barrel, Brain, Wine!</h2>

<p>This is a variation on Rock, Paper, Scissors. In this version, barrel beats wine, wine beats brain, and brain beats barrel. Click on the option you want to choose and see if you win against the computer!</p>

<img id="player" src="images/player.png" alt="player">
    <img id= "computer" src="images/computer.png" alt="computer">
    <br>
<input type="button" onclick="brain()" value="Brain">
    <input type="button" onclick="wine()" value="Wine">
    <input type="button" onclick="barrel()" value="Barrel">
    <br>
    <div id="whowon"></div>
         
    <br>
    <div id="userscore"></div>
       
    <br>
    <div id="computerscore"></div>
        
    
    <br>
    <input type="button" value="Reset" onClick="window.location.reload()">
</body>

</html>


