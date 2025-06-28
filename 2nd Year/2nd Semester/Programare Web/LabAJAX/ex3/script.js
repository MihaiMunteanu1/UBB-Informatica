window.onload = function() {
    var inputs = document.querySelectorAll('#formular input');
    var saveButton = document.getElementById('save');
    var userList = document.getElementById('lista');
    var users = [];

    var xhr = new XMLHttpRequest();
    xhr.open('GET', 'users.php', true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4 && xhr.status === 200) {
            try {
                users = JSON.parse(xhr.responseText);
                users.forEach(function(user) {
                    var listItem = document.createElement('li');
                    listItem.innerHTML = user.id;
                    userList.appendChild(listItem);

                    listItem.addEventListener('click', function() {
                        if (saveButton.disabled === false) {
                            var saveChanges = confirm('You have unsaved changes. Do you want to save them?');
                            if (saveChanges) {
                                saveButton.click();
                            }
                        }

                        document.getElementById('id').value = user.id;
                        document.getElementById('nume').value = user.nume;
                        document.getElementById('prenume').value = user.prenume;
                        document.getElementById('telefon').value = user.telefon;
                        document.getElementById('email').value = user.email;

                        saveButton.disabled = true;
                    });
                });
            } catch (e) {
                console.error('JSON parse error:', e);
            }
        }
    };
    xhr.send();

    inputs.forEach(function(input) {
        input.addEventListener('input', function() {
            saveButton.disabled = false;
        });
    });

    saveButton.addEventListener('click', function() {
        var id = document.getElementById('id').value;
        var nume = document.getElementById('nume').value;
        var prenume = document.getElementById('prenume').value;
        var telefon = document.getElementById('telefon').value;
        var email = document.getElementById('email').value;

        var params = 'id=' + encodeURIComponent(id) +
            '&nume=' + encodeURIComponent(nume) +
            '&prenume=' + encodeURIComponent(prenume) +
            '&telefon=' + encodeURIComponent(telefon) +
            '&email=' + encodeURIComponent(email);

        var xhrUpdate = new XMLHttpRequest();
        xhrUpdate.open('POST', 'update.php', true);
        xhrUpdate.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhrUpdate.onreadystatechange = function() {
            if (xhrUpdate.readyState === 4 && xhrUpdate.status === 200) {
                console.log(xhrUpdate.responseText);
                location.reload();
            }
        };
        xhrUpdate.send(params);
    });
};