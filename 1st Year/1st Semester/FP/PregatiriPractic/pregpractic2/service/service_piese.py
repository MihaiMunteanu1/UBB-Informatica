from domain.piesa import Piesa
import random,string
class ServicePiese:
    def __init__(self,repo_piese,valid_piese):
        self.__repo_piese=repo_piese
        self.__valid_piese=valid_piese

    def add_piesa(self,id,titlu,regizor,gen,durata):
        piesa=Piesa(id,titlu,regizor,gen,durata)
        self.__valid_piese.valideaza_piesa(piesa)
        self.__repo_piese.add_piesa(piesa)

    def modifica(self,titlu,regizor,new_gen,new_durata):
        self.__valid_piese.valideaza_piesa2(titlu,regizor,new_gen,new_durata)
        self.__repo_piese.modifica(titlu,regizor,new_gen,new_durata)

    def export(self):
        toate_piese=self.get_all()
        result=[]
        for piesa in toate_piese:
            result.append(piesa)
        result.sort(key=lambda x:x.get_regizor())
        result.sort(key=lambda x:x.get_titlu())
        return result

    def random(self,numere):
        piese_generate=[]
        for i in range(0,numere):
            id=self.genereaza_id_piesa_random()
            titlu=self.generare_titlu()
            regizor=self.generare_regizor()
            gen=self.generare_gen()
            durata=self.generare_durata()
            piesa=Piesa(id,titlu,regizor,gen,durata)
            self.__valid_piese.valideaza_piesa(piesa)
            self.__repo_piese.add_piesa(piesa)
            piese_generate.append(piesa)
        return piese_generate

    def generare_titlu(self):
        lungime_titlu = random.randint(8, 12)
        vocale = "aeiou"
        consoane = "".join([c for c in string.ascii_lowercase if c not in vocale])

        titlu_generat = ""
        for i in range(lungime_titlu):
            if i % 2 == 0:
                titlu_generat += random.choice(consoane)
            else:
                titlu_generat += random.choice(vocale)

        titlu_generat = titlu_generat.capitalize()
        titlu_generat += " " + random.choice(string.ascii_uppercase) + random.choice(consoane)
        return titlu_generat

    def generare_gen(self):
        lista=['Comedie','Drama','Satira','Altele']
        gen_piesa=random.choice(lista)
        return gen_piesa

    def generare_regizor(self):
        return self.generare_titlu()

    def genereaza_id_piesa_random(self):
        return random.randint(1, 10000)

    def generare_durata(self):
        return random.randint(100,1000)

    def get_all(self):
        return self.__repo_piese.get_all()