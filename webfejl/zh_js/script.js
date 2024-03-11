const numObj = document.querySelector("#num")
const btnObj = document.querySelector("#btn")
const ulObj = document.querySelector("ul")
const spanObj = document.querySelector("span")

btnObj.addEventListener("click", onInput)
ulObj.addEventListener("click", onClick)

let liCntr = 0

setSpan()

function onInput(e) {
    let num = numObj.value.replace(/\s/g, "")
    if (!isNaN(num) && liCntr < 5 && isGreaterThanAll(num)) {
        var li = document.createElement("li")
        li.appendChild(document.createTextNode(num))
        ulObj.appendChild(li)
        liCntr++
        resetColor()
        if (liCntr === 5) {
            btnObj.disabled = true
        }
    }
    setSpan()
}

function onClick(e) {
    if (e.target.matches("ul > li")){
        e.target.style.color = "red"
    }
    setSpan()
}

function resetColor() {
    let items = ulObj.getElementsByTagName("li")
    for (let i = 0; i < items.length; i++) {
        items[i].style.color = "black"
    }
    setSpan()
}

function setSpan() {
    let items = ulObj.getElementsByTagName("li")
    let sum = 0
    let cntr = 0
    for (let i = 0; i < items.length; i++) {
        if (items[i].style.color === "red") {
            sum += parseFloat(items[i].innerText.replace(/\s/g, ""))
            cntr++
        }
    }

    if (cntr === 0) {
        spanObj.innerText = 0
    } else {
        spanObj.innerText = (sum / cntr).toString()
    }
}

function isGreaterThanAll(number) {
    let items = ulObj.getElementsByTagName("li")
    for (let i = 0; i < items.length; i++) {
        if (parseFloat(items[i].innerText) >= number) {
            return false
        }
    }
    return true
}