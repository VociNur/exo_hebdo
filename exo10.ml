type automate =
  {
    initial : int list;
    final : bool array;
    delta : int list array array;
    delta_eps : int list array;
  }

let nbr_lettres = 2;;

let cloture (m:automate) (q:int) : int list =
  let nb_etats = Array.length m.final in
  let vus = Array.make nb_etats false in
  let rec aux (q:int) (acc:int list) : int list =
    vus.(q) <- true;
    List.fold_left
      (fun acc r -> if not vus.(r) then aux r acc else acc) (q::acc) m.delta_eps.(q)
  in aux q [];;

let l_pos (l:'a list) =
  List.filter (fun x -> x>=0) l;;

let random_auto (n:int) : automate =
  
  Random.self_init ();
  let ini = l_pos (List.init n (fun x -> if Random.int 100 > 75 then x else -1)) in
  
  let fin = Array.init n (fun x -> Random.int 100 > 75) in
  let delta = Array.init n (fun x -> [||]) in
  for i=0 to n-1 do
    delta.(i) <- Array.make nbr_lettres [];
    for l=0 to nbr_lettres-1 do
      delta.(i).(l) <- l_pos (List.init n (fun x -> if Random.int 100 > 70 then x else -1))
    done;
  done;

  
  let delta_eps = Array.init n ((fun x -> l_pos (List.init n (fun x -> if Random.int 100 > 70 then x else -1)))) in
  {initial=ini;final=fin;delta=delta;delta_eps=delta_eps};;

let lit_lettre (a:automate) (c:char) (actual:bool array) =
  let n = Array.length a.final in
  let next = Array.make n false in
  let delta = a.delta in
  let nbr = int_of_char c in
  for i=0 to n-1 do
    if actual.(i) then
      begin
        List.iter (fun x -> next.(x) <- true) delta.(i).(nbr)
      end
  done;
  for i=0 to n-1 do
    actual.(i) <- next.(i)
  done;;

let print_int_tab (tab:'a array) =
  
  Array.iter (fun x -> Printf.printf "%d" x) tab;
  print_string "\n";;

let print_bool_tab (tab:bool array) =
  Array.iter (fun x -> Printf.printf "%d" (if x then 1 else 0)) tab;
  print_string "\n";;



let lit_eps (a:automate) (actual:bool array) =
  let n = Array.length a.final in
  let next = Array.make n false in
  let delta = a.delta_eps in
  
  for i=0 to n-1 do
    if actual.(i) then
      begin
        List.iter (fun x ->
            begin
              next.(x) <- true
             
            end
          ) delta.(i)
        
      end
  done;
  for i=0 to n-1 do
    actual.(i) <- next.(i)
  done;;



  
  
let accepte (a:automate) (s:string) : bool =
  let n = Array.length a.final in
  let actual = Array.make n false in
  let m = String.length s in

  (*init*)
  List.iter (fun x-> actual.(x) <- true) a.initial;
  for i=0 to m-1 do (*on lit ε, lettre, ε, lettre … ε*)
    print_bool_tab actual;
    lit_eps a actual;
    Printf.printf "Lit eps\n";
    print_bool_tab actual;
    lit_lettre a s.[i] actual;
    Printf.printf "Lit %d\n" (int_of_char (s.[i]));
  done;
  print_bool_tab actual;
  lit_eps a actual;
  print_bool_tab actual;
  Array.exists Fun.id (Array.map2 (fun x y -> x&&y) actual a.final);; (*intersection des états après avoir tout lu et les états acceptants*)



let int_to_ascii (l:'a list) =
  List.fold_left (fun acc x -> acc ^ String.make 1 (char_of_int(x))) "" l;;

let a1 = random_auto 5;;
let mot = int_to_ascii [0;1;0];;
String.length mot;;
accepte a1 mot;;
