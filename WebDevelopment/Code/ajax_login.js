// ajax_login.js
//  Ajax JavaScript code for the ajax_loginForm.php document

/********************************************************/
// function chechUserName
//  parameter: userName
//  action: create the XMLHttpRequest object, register the
//          handler for onreadystatechange, prepare to send
//          the request (with open), and send the request,
//          along with the userName, to the server
//  

function checkUserName(userName) {
  var xhr = new XMLHttpRequest();

// Register the embedded handler function
  xhr.onreadystatechange = function () {
  
    if (xhr.readyState == 4 && xhr.status == 200) {
		
		var result = (xhr.responseText);
	    // Strip out new line chars and whitespace 
		result = result.replace(/(\r\n|\n|\r)/gm,"");
		
		if (result == "0")  {
			alert ("Username is not in database");
			document.getElementById("userName").innerHTML = "Enter a Valid username or sign-up";
			document.getElementById("userName").focus();
			document.getElementById("userName").style.backgroundColor = "red";
	   } else {
			if (result = "1")  {
				document.getElementById("userName").style.backgroundColor = "green";
			}  else  {
				document.getElementById("userName").style.backgroundColor = "yellow";
			}
		}
	}
  }
  xhr.open("GET", "ajax_user_login.php?userName=" + userName, true);
  xhr.send(null);


}


