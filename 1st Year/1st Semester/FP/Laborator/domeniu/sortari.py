import random
class Sort:
    @staticmethod
    def merge_sort(array, key=lambda x: x,compare=None):
        if len(array) <= 1:
            return array

        mijloc = len(array) // 2
        left = array[:mijloc]
        right = array[mijloc:]

        left = Sort.merge_sort(left, key,compare)
        right = Sort.merge_sort(right, key,compare)

        return Sort.merge(left, right, key,compare)

    @staticmethod
    def merge(left, right, key, compare):
        result = []
        i = j = 0

        while i < len(left) and j < len(right):
            if key(left[i]) < key(right[j]):
                result.append(left[i])
                i += 1
            elif key(left[i]) == key(right[j]):
                if compare is not None and compare(left[i], right[j]) < 0:
                    result.append(left[i])
                    i += 1
                else:
                    result.append(right[j])
                    j += 1
            else:
                result.append(right[j])
                j += 1

        result.extend(left[i:])
        result.extend(right[j:])
        return result
    """
    O variantă de sortare de selecție care ordonează siruri găsind mai întâi cea mai mică valoare, apoi mutând în 
    mod repetat toate elementele cu acea valoare în locația lor finală și găsind cea mai mică valoare pentru următoarea trecere. 
    Aceasta este mai eficientă decât selection sort dacă există multe valori duplicate.
    Analiza complexitatii functiei Bingo Sort:
    Average Case si Worst Case: Θ(M*N) unde M=numarul de elemente de elemente distincte
    si N=lungimea sirului
    Best Case: Θ(N + M^2)
    """
    @staticmethod
    def bingo_sort(arr, key=lambda x: x):
        while not Sort.is_sorted(arr, key):
            random.shuffle(arr)

    @staticmethod
    def is_sorted(arr, key):
        return all(key(arr[i]) <= key(arr[i + 1]) for i in range(len(arr) - 1))