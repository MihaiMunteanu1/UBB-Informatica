window.onload = function() {
    var page = 1;

    function fetchData() {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                var response = JSON.parse(this.responseText);
                var data = response.data;
                var total = response.total;
                console.log(data);
                var table = document.getElementById("tabela");
                table.innerHTML = "<tr><th>Nume</th><th>Prenume</th><th>Telefon</th><th>Email</th></tr>";
                for (var i = 0; i < data.length; i++) {
                    var row = table.insertRow(-1);
                    row.insertCell(0).innerHTML = data[i].nume;
                    row.insertCell(1).innerHTML = data[i].prenume;
                    row.insertCell(2).innerHTML = data[i].telefon;
                    row.insertCell(3).innerHTML = data[i].email;
                }
                for (var i = data.length; i < 3; i++) {
                    var row = table.insertRow(-1);
                    row.insertCell(0).innerHTML = "";
                    row.insertCell(1).innerHTML = "";
                    row.insertCell(2).innerHTML = "";
                    row.insertCell(3).innerHTML = "";
                }
                document.getElementById("prev").disabled = page == 1;
                document.getElementById("next").disabled = page * 3 >= total;
            }
        };
        xmlhttp.open("GET", "users.php?page=" + page, true);
        xmlhttp.send();
    }

    document.getElementById("prev").addEventListener("click", function () {
        page--;
        fetchData();
    });

    document.getElementById("next").addEventListener("click", function () {
        page++;
        fetchData();
    });

    fetchData();
}