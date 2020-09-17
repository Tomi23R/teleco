// ssh -X est011@150.244.59.74\r \tContraseña: administrador"
// Hay que instalar express y body parser(esto es para los get y los post)

// Inicializamos los paquetes que hemos instalado
const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose')
var session = require('express-session');

// Incializamos nuestra aplicacion con express
const app = express();

// Inicializamos nuestra app con mongoose
mongoose.connect('mongodb://localhost:27017/est011db', {useNewUrlParser: true , useUnifiedTopology: true});
const db = mongoose.connection;
db.on('error', console.log.bind(console, "Error while connecting to database."));
db.once('open', function(callback){
    console.log("Correct connection with the database");
})


// Declaramos nuestro fichero de archivos estaticos
app.use(express.static(__dirname + '/static'));

// Declaramos el body parser para los forms
app.use(bodyParser.urlencoded({extended: true}))
app.use(bodyParser.json());

// Declaramos nuestra variable de sesion
app.use(session({secret: 'CodigoBienDeSecreto',saveUninitialized: true,resave: true}));

// Seteamos el tipo de view, ejs, para poder enviar datos a los templates
app.set('view engine', 'ejs');

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaracion de las vistas de tipo GET

// Vista del indice de la aplicacion
app.get('/', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada mandamos la sesion al indice
    if(sess.name){
        // Devolvemos al indice
        res.render('index', {sesion: sess.name})
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        res.render('index', {sesion: null});
    }
});

// Vista del indice de la aplicacion
app.get('/index', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada mandamos la sesion al indice
    if(sess.name){
        // Devolvemos al indice
        res.render('index', {sesion: sess.name})
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        res.render('index', {sesion: null});
    }
});

// Vista del login de la aplicacion
app.get('/login', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que no se ha podido realizar post
    if(sess.name){
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        res.render('login');
    }
});

// Vista de inicio de sesion de la aplicacion
app.get('/sign_in', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que no se ha podido realizar post
    if(sess.name){
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        res.render('iniciasesion');
    }
});

// Vista de la pagina de registro de la aplicacion
app.get('/sign_up', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que no se ha podido realizar post
    if(sess.name){
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        res.render('formulario');
    }
});

// Vista de salir de sesion de la aplicacion
app.get('/sign_out', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que podemos borrarla para salir del usuario
    if(sess.name){
        req.session.destroy();
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada volvemos a la pagina de incio de sesion
    else{
        res.redirect('/');
    }
});

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaracion de las vistas de tipo POST

// Post para registrarse en la aplicacion
app.post('/sign_up', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que no se ha podido realizar post
    if(sess.name){
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        // Obtenemos los valores del formulario
        var DNI = req.body.DNI;
        var contrasena = req.body.contrasena;
        var correo = req.body.correo;
        var nombre = req.body.nombre;
        var edad = req.body.edad
        var data = {
            "DNI": DNI,
            "contrasena":contrasena,
            "correo":correo,
            "nombre":nombre,
            "edad":edad
        }

        // Antes de registro es necesario comprobar si el usuario ya existe
        db.collection('usuarios').findOne({'DNI' : DNI}, (error, exist) => {
            if (exist && !error){
                // Como existe el usuario no continuamos con el registro
                console.log('Este usuario ya existe, no se puede completar el registro');
                res.redirect('/sign_up');   
            }else{
                // Si no existe el usuario continuamos con el registro
                console.log('No existe el usuario asi que procedemos al registro');
                db.collection('usuarios').insertOne(data,function(err, collection){
                    if (err) 
                        throw err;
                    console.log("Usario anadido correctamente");
                });

                // Seteo cookies de incio de sesion
                sess.name = nombre;

                // Devuelvo a la pantalla de incio
                res.redirect('/');
            }
        });
    }
});

// Post para inciar sesion en la aplicacion
app.post('/sign_in', (req, res) => {
    // Primero comprobamos si alguien ha iniciado sesion antes
    sess = req.session;
    // Si la sesion esta iniciada significa que no se ha podido realizar post
    if(sess.name){
        // Devolvemos al indice
        res.redirect('/');
    }
    // Si la sesion no esta iniciada tratamos el post
    else{
        dni = req.body.DNI;
        contrasena = req.body.contrasena;
        
        // Comprobamos si existe usuario con ese dni y contrasena
        db.collection('usuarios').findOne({'DNI' : dni, 'contrasena' : contrasena}, (error, exist) => {
            if (exist && !error){
                // Como existe el usuario y la contrasena es correcta se incia sesion
                console.log('El usuario y contrasena son correctos procedemos al login');
                // Seteo las cookies y mando al indice
                sess.name = exist.nombre;
                res.redirect('/');   
            }else{
                // Aqui devuelvo al login
                console.log('Error en el usuario y contrasena');
                res.redirect('/sign_in');
            }
        });
    }
});

// Por ultimo creamos la view que soporta el error 404
app.use(function(req, res, next) {
    res.status(404);
    res.send('404: File Not Found');
});


app.listen(8011, () => console.log('Listening on port 8011...'));