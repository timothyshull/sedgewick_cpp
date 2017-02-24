def insertion_sort(input_list):
    if len(input_list) > 1:  # otherwise, no need to sort it
        marker = input_list.first()
        while marker != input_list.last():
            pivot = input_list.after(marker)  # next item to place
            value = pivot.element()
            if value > marker.element():  # pivot is already sorted
                marker = pivot  # pivot becomes new marker
            else:  # must relocate pivot
                walk = marker  # find leftmost item greater than value
                while walk != input_list.first() and input_list.before(walk).element() > value:
                    walk = input_list.before(walk)
                input_list.delete(pivot)
                input_list.add_before(walk, value)  # reinsert value before walk
