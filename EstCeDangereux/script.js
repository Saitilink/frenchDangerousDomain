const main_fichier = "https://dl.red.flag.domains/red.flag.domains.txt";
async function chargerTxt() {  
    try {
        texte = document.getElementById("barre").value;
        const remove = document.getElementById("Div Temporaire");
        if (remove != null) {

            remove.remove()}
        const nouvDiv = document.createElement("div");
        nouvDiv.id = "Div Temporaire"
        nouvDiv.innerHTML = "Test";
        but = document.getElementById("bouton")   
        but.appendChild(nouvDiv)
        console.log(texte)
    }
    catch(error){
        console.log(error)
    }
}