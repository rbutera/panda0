// Simulate typing
"use strict";

type();
function type() {

    // Set up variables and methods.
    var slide, canvas, brush, data, target, pos;
    type.start = start;
    type.stop = stop;
    type.end = end;
    type.key = key;
    return;

    // Given a slide element and canvas overlay, start the animation.
    // Insert a delay to allow the browser layout to settle.
    function start(element, overlay) {
        init(element, overlay);
        var from = data.textContent;
        var to = "";
        for (var i=0; i<from.length; i++) {
            var ch = from.charAt(i);
            if (ch != '\n') ch = ' ';
            to = to + ch;
        }
        target.innerHTML = to;
    }

    // Go straight to the end of the animation, either to prepare for printing,
    // or else because the user has moved back from the following slide. 
    function end(element, overlay) {
        init(element, overlay);
        target.innerHTML = data.textContent;
    }

    // Called from start and end to initialise
    function init(element, overlay) {
        slide = element;
        canvas = overlay;
        brush = canvas.getContext("2d");
        data = slide.querySelector(".data");
        target = slide.querySelector(".target");
        pos = 0;
    }

    function stop() {}

    function key(k) {
        var from = data.textContent;
        if (pos >= from.length) return;
        var ch = from.charAt(pos);
        var to = target.textContent;
        to = to.substring(0, pos) + ch + to.substr(pos+1);
        target.innerHTML = to;
        pos++;
    }
}
