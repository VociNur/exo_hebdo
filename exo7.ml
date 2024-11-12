
let rec aux (values : int list) (actual_sum:int )(s:int) =
  if actual_sum > s then (0, [])
  else
    begin
      match values with
      |[] -> begin
          (* print_int actual_sum;*)
          (actual_sum, [])
        end
        |a::q -> begin
            let (r1, l1) = aux q (actual_sum+a) s in
            let (r2, l2) = aux q (actual_sum) s in
            if r1 > r2 then
              (r1, a::l1) else
              (r2, l2)
          end
    end;;

let sub_set_sum (values : int list) (s:int) =
  s = fst (aux values 0 s);;

let _ = sub_set_sum [4;1;1;5] 6;;
