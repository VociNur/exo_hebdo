
type 'a automate =
  {acceptant : bool array; delta : ('a, int) Hashtbl.t array}

let () = Random.self_init ();;

let random_automate ()=
  let n = 10 +  Random.int 10 in (*nbr états*)
  let acceptant = Array.make n false in (*états acceptants*)
  let delta = Array.make n (Hashtbl.create n) in 
  for i=0 to n-1 do
    if (Random.int 100) > 50 then acceptant.(i) <- true;(*1 état sur 2 est acceptant (random)*)
    for j=(int_of_char 'a') to (int_of_char 'z') do
      let next = Random.int (1+n) in
      if next < n then (*afin d'avoir une fonction partielle, le cas "=n" correspond à aucun état défini*)
        begin
          Hashtbl.add delta.(i) (char_of_int j) next; (*on associe à delta(i, a) l'état next*)
          Printf.printf "%d + %c -> %d\n" i (char_of_int j) next;
          (* Printf.printf "%d\n" (Hashtbl.find delta.(i) (char_of_int j)); tout est bon il renvoie le bon nombre*)
        end
    done;
  done;
  
  {acceptant=acceptant; delta = delta};;


let au = random_automate ();;
Printf.printf "----------------------------";;
let accepte (auto:'a automate) (mot:'a array) : bool =
  let actual_edge = ref 0 in (* le départ est 0*)
  let {acceptant=acceptant; delta=delta} = auto in
  let can_be_read = ref true in (*si le mot peut être lu*)
  Array.iter (fun x ->
      if !can_be_read then (*si on n'a pas pu lire une lettre, ne sert à rien de continuer*)
        begin
          
          if Hashtbl.mem delta.(!actual_edge) x then (*si on peut lire la suite*)
            begin
              Printf.printf "%d + %c devient %d" !actual_edge x (Hashtbl.find delta.(!actual_edge) x);
              actual_edge := Hashtbl.find delta.(!actual_edge) x; (*problème à ce moment là, il ne lit pas correctement la suite*)
              Printf.printf "%d\n" !actual_edge;
            end
          
          else
            can_be_read := false;
          
          Printf.printf "actual: %d\n" !actual_edge;
          
          
        end
    ) mot;
  
  !can_be_read && acceptant.(!actual_edge);;

print_string "-----";;
let _ = accepte au [|'a';'b'|];;
