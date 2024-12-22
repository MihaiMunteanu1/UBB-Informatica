class ValidatorStudent:
    def valideaza_student(self,student):
        erori=""
        if student.get_id_student()<0:
            erori+="id invalid\n"
        if student.get_nume()=="":
            erori+="nume invalid\n"
        if student.get_grup()<0:
            erori+="grup invalid\n"
        if len(erori)>0:
            raise Exception(erori)