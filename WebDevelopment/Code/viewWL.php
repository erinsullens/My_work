<?php
session_start();


?>
<!DOCTYPE HTML SYSTEM>
<html>
<head>
<title>Erin' s Project</title>
    <link rel="stylesheet" href="style.css">
</head>
<h2>Wine Collection - View Wishlist</h2>
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
    
<?php
if (isset($_SESSION['valid_user'])) {    
require_once('connect.php');
$mId = $_SESSION['memberId'];

$query = "SELECT winery, wineType, vintage, notes, wineColor, price FROM wineWishlist WHERE memberId = '$mId'";

$response = @mysqli_query($dbc, $query);

if($response){
    
    echo '<table align="left"
    cellspacing="5" cellpadding="8">
    
    <tr><td align="left"><b>Winery</b></td>

    <td align="left"><b>Wine Type</b></td>
    <td align="left"><b>Vintage</b></td>

    <td align="left"><b>Notes</b></td>

        <td align="left"><b>Wine Color</b>
        <td align="left"><b>Price</b></td></tr>';

    
    while($row = mysqli_fetch_array($response)){
        
        echo '<tr><td align="left">' .
        $row['winery'] . '</td><td align="left">' .
        $row['wineType'] . '</td><td align="left">' .
        $row['vintage'] . '</td><td align="left">' .
        $row['notes'] . '</td><td align="left">' .
        $row['wineColor'] . '</td><td align="left">' .
        $row['price'] . '</td><td align="left">';

        echo '</tr>';
        
    }
    echo '</table>';
} else {
    echo "couldn't show database";
    echo mysqli_error($dbc);
}

mysqli_close($dbc);
}else{
    
    echo "You need to be logged in to see this feature";
}
?>    
    
    
    
</html>
