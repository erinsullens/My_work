var i = 1;
var path = new Array();
 
// LIST OF IMAGES
path[0] = "images/pic1.png";
path[1] = "images/pic2.png";
path[2] = "images/pic3.png";
path[3] = "images/pic4.png";
path[4] = "images/pic5.png";

//show next image
function swapImage()
{
    if(i < path.length - 1) i++; else i = 0;
   document.getElementById("image").src = path[i];
   
   
}

function prev()
{
    if(i === 0) i = path.lenth - 1; else i--;
   document.getElementById("image").src = path[i];
}


