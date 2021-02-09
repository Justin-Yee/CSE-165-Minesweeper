/*-------------Constant Cell Display Functions-------------------*/
function updateBoard(state){
	//var sel = "#" + x.toString()+ "-" + y.toString();
	var sel = "#1-1";
	$(sel).html(state["type"]);
		return;
}

function createGrid(data){

	var result = "";
	//Displays Board / Button Text
	for (var i in data){
		var cr = "<tr>";

		for (var j in data[i]){
			if(data[i][j]["type"] == "hidden" || data[i][j]["type"] == "flag" )
				cr = cr + "<td id=\""+ i.toString()+ "-" + j.toString()+ "\"><button>"+data[i][j]["type"]+"</button></td>";
			else if(data[i][j]["count"] == undefined)
			cr = cr + "<td id=\""+ i.toString()+ "-" + j.toString()+ "\">"+data[i][j]["type"]+"</td>";
			else
			cr = cr + "<td id=\""+ i.toString()+ "-" + j.toString()+ "\">"+data[i][j]["count"]+"</td>";
		}

		cr = cr + "</tr>\n";
		result = result + cr;

	}
	$("#grid").html(result);

	//if winState != 0; unable to act
	if(data["win"] == '2'){
		alert("Loss");
		return;
	}
	else if(data["win"] == '1'){
		alert("Won");
		return;
	}

	for (var i in data){
		var cr = "<tr>";

		for (var j in data[i]){
			var theID = "#" + i.toString()+ "-" + j.toString();
			$(theID).mousedown({row: i, col: j}, function(e){
				var x = e.data.row;
				var y = e.data.col;				
				var press = e.which;
				if(press == 1)
					press = "left";
				else
					press = "right";

			$.get("/handle", {"x": x, "y": y, "btn":press}, function(response){
				var data = JSON.parse(response);
				var board = data["board"];
				
				if(data["win"] == '2'){
					alert("Loss");
				}
				else if(data["win"] == '1'){
					alert("Won");
				}
			
			createGrid(board);
			});
				//alert("Clicked on a square (" + x + ", " + y + ")");
			});

		}
	}
	return;
};

$(document).ready(function(){
	$("#GenTableBox").hide();
	$("#GenDisplay").show();
	var x = 0; 

	$(document).contextmenu(function() {
		return false;
	});

	$.get("/init",{}, function(response){
		console.log("Initalized");
		var data = JSON.parse(response);
		var board = data["board"];

		//if winState != 0; unable to act
		if(data["win"] == '2'){
			alert("Loss");
		}
		else if(data["win"] == '1'){
			alert("Won");
		}

		createGrid(board);

		return;
	});

	/*------------Table Gen Functions---------------*/
	 $("#genDisplay_btn").click(function(){
		
		if(x == 0){
			x = 1;
			$("#GenTableBox").show();}
		else{
			x = 0;
			$("#GenTableBox").hide();}
		
	 });
	
	 $("#genBoard_btn").click(function(){
		var rowSize = $("#RowInput").val();
		var colSize = $("#ColInput").val();
		var bombNum = $("#BombInput").val();
		//alert(rowSize +" "+colSize +" "+bombNum);
		/* $.get("/init", {rowSize: rowSize, colSize: colSize, bombNum: bombNum}, function(response){
			var details = JSON.parse(response);
			if (details["success"]){
				display(board);
			}
			else {*/
			if(rowSize * colSize < bombNum-1){
			alert("Improper Inputs");
			$("#RowInput").val("");
			$("#ColInput").val("");
			$("#BombInput").val("");
			$("#GenTableBox").hide();
			x = 0;
			}
			else{
			alert("Function Not Supported");
			$("#RowInput").val("");
			$("#ColInput").val("");
			$("#BombInput").val("");
			$("#GenTableBox").hide();
			x = 0;
			//$("#RowInput").focus();
			}
			

	 });

	/*-------------Table Click Functions-------*/

	$("#rest_btn").click(function(){
		console.log("Reset Button Clicked");
		reset();
	});

});

function reset(){

	$.get("/init", { }, function(response) {
		var data = JSON.parse(response);
		var board = data["board"];
		////console.log(data);
		//console.log("Hi");
		createGrid(board);

		$("td").empty();
	});

	console.log("Reset Function Ran");
}
