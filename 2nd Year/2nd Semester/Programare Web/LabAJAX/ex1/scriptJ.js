function getPlecari() {
    $.ajax({
        url: "plecari.php",
        method: "GET",
        success: function(data) {
            $('#orasPlecare').html(data);
        }
    });
}

function getSosiri(value) {
    $.ajax({
        url: "sosiri.php",
        method: "GET",
        data: { name: value },
        success: function(data) {
            $('#orasSosire').html(data);
        }
    });
}