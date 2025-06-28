$(document).ready(function() {
    var users;
    var formChanged = false;

    $.ajax({
        url: 'users.php',
        type: 'GET',
        dataType: 'json',
        success: function(users) {
            $.each(users, function(i, user) {
                var listItem = $('<li>').text(user.id);
                $('#lista').append(listItem);

                listItem.click(function() {
                    if (formChanged) {
                        var saveChanges = confirm('You have unsaved changes. Do you want to save them?');
                        if (saveChanges) {
                            $('#save').click();
                        }
                    }
                    $('#id').val(user.id);
                    $('#nume').val(user.nume);
                    $('#prenume').val(user.prenume);
                    $('#telefon').val(user.telefon);
                    $('#email').val(user.email);

                    $('#save').prop('disabled', true);
                    formChanged = false;
                });
            });
        }
    });

    $('#formular input').on('input', function() {
        console.log('input changed');
        $('#save').prop('disabled', false);
        formChanged = true;
    });

    $('#save').click(function() {
        var id = $('#id').val();
        var nume = $('#nume').val();
        var prenume = $('#prenume').val();
        var telefon = $('#telefon').val();
        var email = $('#email').val();

        $.ajax({
            url: 'update.php',
            type: 'POST',
            data: {
                id: id,
                nume: nume,
                prenume: prenume,
                telefon: telefon,
                email: email
            },
            success: function(data) {
                console.log(data);
                location.reload();
            }
        });
        formChanged = false;
    });
});