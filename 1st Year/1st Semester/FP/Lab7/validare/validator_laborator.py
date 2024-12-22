class ValidatorLaborator:
    def validate_laborator(self, laborator):
        errors = ""
        if laborator.get_numar_problema() < 0:
            errors += "numar problema invalid!\n"
        if laborator.get_descriere() == "":
            errors += "descriere invalida!\n"
        if laborator.get_deadline()=="":
            errors+="deadline invalid!\n"
        if len(errors) > 0:
            raise Exception(errors)