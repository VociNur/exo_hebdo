type regexp =
  |Empty
  |Epsilon
  |Letter of char
  |Union of regexp * regexp
  |Concat of regexp * regexp
  |Star of regexp

let rec is_empty (r:regexp) : (bool * regexp) =
  match r with
  | Empty -> (true, Empty)
  | Epsilon -> (false, r)
  | Letter a -> (false, r)
  | Union (r1, r2) -> let ((empty1, reg1), (empty2, reg2)) = (is_empty r1, is_empty r2)
                      in
                      begin
                        match (empty1, empty2) with
                        | false, false -> (false, Union (reg1, reg2))
                        |true, false -> (false, reg2)
                        | false, true -> (false, reg1)
                        | true, true -> (true, Empty)
                      end
  | Concat (r1, r2) -> let ((empty1, reg1), (empty2, reg2)) = (is_empty r1, is_empty r2)
                      in
                      begin
                        match (empty1, empty2) with
                        | false, false -> (false, Concat (reg1, reg2))
                        | _, _ -> (true, Empty)
                      end
  |Star r1 -> let (empty1, reg1) = is_empty r1 in
              begin
                match (empty1) with
                |false -> (false, Star reg1)
                |true -> (false, Epsilon)
              end


let _ = is_empty (Union( Empty, Letter 'a'));;
let _ = is_empty (Concat(Letter 'a', Empty));;
let _ = is_empty (Star (Empty));; 
(*on aurait pu modifier pour aussi enlever les ε, et 
