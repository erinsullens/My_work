//initialize variables for score, and array to hold choices for the computer
var computerChoice = ["brain", "wine", "barrel"];
var userWins = 0;
var computerWins = 0;
var ties = 0;

//function to have the computer randomly choose brain, wine or barrel
function cpChoice() {
    //"use strict";
    var randomNum = Math.floor((Math.random() * 3));
    if (randomNum===0)
        document.getElementById("computer").src="images/brain.png";
    if (randomNum===1)
        document.getElementById("computer").src="images/wine.png";
    if (randomNum===2)
        document.getElementById("computer").src="images/barrel.png";
    
    return randomNum;
}

//function to determine who wins
function whoWins(userChoice, computer) {
    //write out the score
    document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
    "use strict";
    //tie senario
    if (userChoice === computer) {
        document.getElementById("whowon").innerHTML = "Tie!";
        
        
    }
    //user chooses barrel
    if (userChoice === "barrel") {
        //computer chooses brain
        if (computer === "brain") {
            document.getElementById("whowon").innerHTML = "Computer Won!";
            computerWins = computerWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
        }
        //computer chooses wine
        if (computer === "wine") {
           document.getElementById("whowon").innerHTML = "You won!";
            userWins = userWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
        }
            
    }
    //user chooses brain
    if (userChoice === "brain") {
        //computer chooses wine
        if (computer === "wine") {
           document.getElementById("whowon").innerHTML = "Computer won!";
            computerWins = computerWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
        }
        //computer chooses barrel
        if (computer === "barrel") {
          document.getElementById("whowon").innerHTML = "You won!";
            userWins = userWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
        }
            
    }
    
    //user chooses wine
    if (userChoice === "wine") {
        //computer chooses brain
        if (computer === "brain") {
         document.getElementById("whowon").innerHTML = "You won!";
            userWins = userWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
        }
        //computer chooses barrel
        if (computer === "barrel") {
         document.getElementById("whowon").innerHTML = "Computer won!";
            computerWins = computerWins + 1;
            document.getElementById("userscore").innerHTML = "Your score: " + userWins;
    document.getElementById("computerscore").innerHTML = "Computer score: " + computerWins;
                
        }
    }
    
    
    
}

//function if user chooses brain. First, change image to brain, then call computerChoice, and put both values into whoWins
function brain() {
    document.getElementById("player").src="images/brain.png";
    //alert("brain");
    var computer = computerChoice[cpChoice()];
    //alert(computer);
    whoWins("brain", computer);
}
//function if user chooses wine. First, change image to wine, then call computerChoice, and put both values into whoWins
function wine() {
    document.getElementById("player").src="images/wine.png";
    //alert("wine");
    var computer = computerChoice[cpChoice()];
    //alert(computer);
    whoWins("wine", computer);
}
//function if user chooses barrel. First, change image to barrel, then call computerChoice, and put both values into whoWins
function barrel() {
    document.getElementById("player").src="images/barrel.png";
    //alert("barrel");
    var computer = computerChoice[cpChoice()];
    //alert(computer);
    whoWins("barrel", computer);
}

