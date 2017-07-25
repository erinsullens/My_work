<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Wine Collection Logout</title>
    <link rel="stylesheet" href="style.css">
</head>
<h2>Wine Collection - Logout</h2>
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
<li><a href= "viewWL.php">View Wishlist</a></li>    <li><a href= "logout.php">Logout</a></li>
</ul>
    </div>
<div id="left"></div>
<div id="right"></div>
<div id="top"></div>
<div id="bottom"></div>
    
<div id="left2"></div>
<div id="right2"></div>
<div id="top2"></div>
<div id="bottom2"></div>

<hr width="50%" ALIGN=LEFT>
    
    
    <?php
    
    session_start();
    
    session_destroy();
    echo "You have been logged out";
    
    
    
    ?>
</body>
</html>
