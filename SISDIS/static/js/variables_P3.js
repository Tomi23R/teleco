//var ejs=New Vue({
//el: "#tline";
//data: {
//ej_actual: [
//{p.ser}
//{p.reps}
//{p.peso}
//{p.dificultad}
//] 
//}
//});
var posts = [{
	ser: 1,
	reps: 1,
	peso: 1,
	dificultad: 0
},
];
var entrenamiento = [
{
		id: 1,
		nombre: 'pressBanca',

		series: [
			{
				ser: 1,
				reps: 1,
				peso: 1,
				dificultad: 0
			},
		]
	},
	{
		id: 2,
		nombre: 'press miltar',

		series: [
			{
				ser: 2,
				reps: 3,
				peso: 3,
				dificultad: 0
			},
		]
	},
	{
		id: 3,
		nombre: 'peso muerto',

		series: [
			{
				ser: 5,
				reps: 6,
				peso: 6,
				dificultad: 0
			},
		]
	},
];


//cloning para las filas y la añades al array cada vez que pulses un boton

var v1 = new Vue({
	el: "#app",
	data: { displayedPosts: posts, ind: 0, },
	methods: {
		camb_ejerc: function (inc){
			var nid=this.ind+inc;
			if (nid<0 || nid>=entrenamiento.length)
				return;
			entrenamiento[this.ind].series = this.displayedPosts;
			this.displayedPosts=entrenamiento[nid].series;
			posts=entrenamiento[nid].series;
			this.ind = nid;		
		},
		
		camb_ejerc_sig: function(){this.camb_ejerc(1)},
		camb_ejerc_ant: function(){this.camb_ejerc(-1)},
		
		increps: function (incremento) {
			if (this.displayedPosts[posts.length - 1].reps >= 0){
				if ((this.displayedPosts[posts.length - 1].reps  !=  0 || incremento>0))
					this.displayedPosts[posts.length - 1].reps += incremento;
				
			}
			//this.displayedPosts[posts.length - 1].reps += incremento;
		},
		incpeso: function (incremento) {
			if (this.displayedPosts[posts.length - 1].peso >= 0){
				if (this.displayedPosts[posts.length - 1].peso !=  0 || incremento>0){
					if (this.displayedPosts[posts.length - 1].peso >= 20)
						incremento = 5*incremento;
					this.displayedPosts[posts.length - 1].peso += incremento;
				}
			}
		},
		incdif: function (incremento) {
			if (this.displayedPosts[posts.length - 1].dificultad >= 0){
				if (this.displayedPosts[posts.length - 1].dificultad !=  0 || incremento>0){
					this.displayedPosts[posts.length - 1].dificultad += incremento;
				}
			}
		},
		addNewRow: function (incremento) {
			var nuevaf = JSON.parse(JSON.stringify(this.displayedPosts[0]));
			this.displayedPosts.push(nuevaf);
			//this.displayedPosts[posts.length - 1].ser += incremento;
			//posts.length = posts.length + 1;
		},
		delunRow: function (incremento) {
			if (posts.length > 1)
				this.displayedPosts.pop();
				//this.displayedPosts[posts.length - 1].ser += incremento;
				//posts.length = posts.length - 1;

		}
	}
})
//innerstorage

<!--
var p1 = 0;
function add() {
	p1 = p1 + 1
	document.getElementById("serie+").innerHTML = p1 + 1;
	//addchild(kostadin)
	var table = document.getElementById("myTable");
	var row = table.insertRow(1);
	var cell1 = row.insertCell(0);
	var cell2 = row.insertCell(1);
	var cell3 = row.insertCell(2);
	var cell4 = row.insertCell(3);
	var cell5 = row.insertCell(4);
	cell1.innerHTML = "";
	cell2.innerHTML = p1;
	cell3.innerHTML = p2;
	cell4.innerHTML = p3;
	cell5.innerHTML = p4;
}

function Delete() {
	document.getElementByClass("myTable").deleteRow(1);
	p1 = p1 - 1
	document.getElementById("serie+").innerHTML = p1 + 1;
}
var p2 = 0;
function myFunctionrepsum() {
	p2 = p2 + 1
	document.getElementById("reps").innerHTML = p2;

}
function myFunctionreprest() {
	p2 = p2 - 1
	document.getElementById("reps").innerHTML = p2;
}

var p3 = 0;
function myFunctionpesosum() {
	p3 = p3 + 2.5
	document.getElementById("peso").innerHTML = p3;

}
function myFunctionpesorest() {
	p3 = p3 - 0.5
	document.getElementById("peso").innerHTML = p3;
}

var p4 = 0;
function myFunctiondifsum() {
	p4 = p4 + (1 / 8)
	document.getElementById("dificultad").innerHTML = p4;

}
function myFunctiondifrest() {
	p4 = p4 - (1 / 8)
	document.getElementById("dificultad").innerHTML = p4;
}

-->