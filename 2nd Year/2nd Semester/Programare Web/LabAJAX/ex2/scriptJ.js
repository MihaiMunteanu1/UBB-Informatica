function fetchData(page) {
    $.ajax({
        url: "users.php",
        type: "GET",
        data: { page: page },
        dataType: 'json',
        success: function(response) {
            console.log(response);
            var data = response.data;
            var total = parseInt(response.total);
            var table = $("#tabela");
            table.html("<tr><th>Nume</th><th>Prenume</th><th>Telefon</th><th>Email</th></tr>");
            for (var i = 0; i < data.length; i++) {
                var row = "<tr><td>" + data[i].nume + "</td><td>" + data[i].prenume + "</td><td>" + data[i].telefon + "</td><td>" + data[i].email + "</td></tr>";
                table.append(row);
            }
            for (var i = data.length; i < 3; i++) {
                var row = "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
                table.append(row);
            }
            $("#prev").prop("disabled", page == 1);
            $("#next").prop("disabled", page * 3 >= total);

            $("#prev").data("page", page);
            $("#next").data("page", page);
        },
        error: function(jqXHR, textStatus, errorThrown) {
            console.log(textStatus, errorThrown);
        }
    });
}

$(document).ready(function() {
    var page = 1;

    fetchData(page);

    $("#prev").click(function() {
        page--;
        fetchData(page);
    });

    $("#next").click(function() {
        page++;
        fetchData(page);
    });
});