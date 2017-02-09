
#include <math.h>
#include <stdlib.h>
#include "geometry.h"
#include "list.h"

int cvxhull(const List* P, List* polygon)
{
    ListElmt* element;

    Point* min,
            * low,
            * p0,
            * pi,
            * pc;

    double z,
            length1,
            length2;

    int count;
    min = list_data(list_head(P));
    for (element = list_head(P); element != NULL; element = list_next(element)) {
        p0 = list_data(element);

        /**************************************************************************
        *                                                                         *
        *  Keep track of the lowest point thus far.                               *
        *                                                                         *
        **************************************************************************/

        if (p0->y < min->y) {
            min = p0;
            low = list_data(element);
        } else {

            /***********************************************************************
            *                                                                      *
            *  If a tie occurs, use the lowest and leftmost point.                 *
            *                                                                      *
            ***********************************************************************/

            if (p0->y == min->y && p0->x < min->x) {
                min = p0;
                low = list_data(element);
            }
        }
    }
    list_init(polygon, NULL);
    p0 = low;
    do {

        /**************************************************************************
        *                                                                         *
        *  Insert the new p0 into the convex hull.                                *
        *                                                                         *
        **************************************************************************/

        if (list_ins_next(polygon, list_tail(polygon), p0) != 0) {
            list_destroy(polygon);
            return -1;
        }

        /**************************************************************************
        *                                                                         *
        *  Find the point pc that is clockwise from all others.                   *
        *                                                                         *
        **************************************************************************/

        count = 0;
        for (element = list_head(P); element != NULL; element =
                                                              list_next(element)) {

            /***********************************************************************
            *                                                                      *
            *  Skip p0 in the list of points.                                      *
            *                                                                      *
            ***********************************************************************/

            if ((pi = list_data(element)) == p0) {
                continue;
            }

            /***********************************************************************
            *                                                                      *
            *  Count how many points have been explored.                           *
            *                                                                      *
            ***********************************************************************/

            count++;

            /***********************************************************************
            *                                                                      *
            *  Assume the first point to explore is clockwise from all others      *
            *  until proven otherwise.                                             *
            *                                                                      *
            ***********************************************************************/

            if (count == 1) {
                pc = list_data(element);
                continue;
            }

            /***********************************************************************
            *                                                                      *
            *  Determine whether pi is clockwise from pc.                          *
            *                                                                      *
            ***********************************************************************/

            if ((z = ((pi->x - p0->x) * (pc->y - p0->y)) - ((pi->y - p0->y) * (pc->x
                                                                               - p0->x))) > 0) {

                /********************************************************************
                *                                                                   *
                *  The point pi is clockwise from pc.                               *
                *                                                                   *
                ********************************************************************/

                pc = pi;
            } else if (z == 0) {

                /********************************************************************
                *                                                                   *
                *  If pi and pc are collinear, select the point furthest from p0.   *
                *                                                                   *
                ********************************************************************/

                length1 = sqrt(pow(pi->x - p0->x, 2.0) + pow(pi->y - p0->y, 2.0));
                length2 = sqrt(pow(pc->x - p0->x, 2.0) + pow(pc->y - p0->y, 2.0));
                if (length1 > length2) {

                    /*****************************************************************
                    *                                                                *
                    *  The point pi is further from p0 than pc.                      *
                    *                                                                *
                    *****************************************************************/

                    pc = pi;
                }
            }
        }

        /**************************************************************************
        *                                                                         *
        *  Prepare to find the next point for the convex hull.                    *
        *                                                                         *
        **************************************************************************/

        p0 = pc;

        /**************************************************************************
        *                                                                         *
        *  Continue until reaching the lowest point again.                        *
        *                                                                         *
        **************************************************************************/

    } while (p0 != low);
    return 0;
}
