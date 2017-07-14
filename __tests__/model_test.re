open Jest;

open Expect;

open Notes_utils;

afterEach (fun () => Model.clearNotes ());

test "it should return empty list initially" (fun () => expect (Model.getNotes ()) |> toEqual []);

test
  "it should add note"
  (
    fun () =>
      {
        let newNote = Model.addNote {text: "test"};
        expect newNote |> toEqual {text: "test", id: "1"}
      }
      [@ocaml.warning "-10"]
  );

test
  "it should get note after adding"
  (
    fun () =>
      {
        let _ = Model.addNote {text: "test"};
        expect (Model.getNotes ()) |> toEqual [{id: "1", text: "test"}]
      }
      [@ocaml.warning "-10"]
  );

test
  "it should add multiple notes"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        expect (Model.getNotes () |> List.length) |> toEqual 3;
        expect (Model.getNotes ()) |>
        toEqual [{id: "1", text: "test1"}, {id: "2", text: "test2"}, {id: "3", text: "test3"}]
      }
      [@ocaml.warning "-10"]
  );

test
  "it should get note by id"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        expect (Model.getNoteById "2") |> toEqual {id: "2", text: "test2"}
      }
      [@ocaml.warning "-10"]
  );

test
  "it should update given note"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        Model.updateNote {text: "test changed", id: "2"};
        let updatedNote = Model.getNotes () |> List.find (fun note => note.id === "2");
        expect updatedNote.text |> toEqual "test changed"
      }
      [@ocaml.warning "-10"]
  );

test
  "it should not update anything if wrong id is given"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        Model.updateNote {text: "test changed", id: "LOL WRONG ID"};
        expect (Model.getNotes ()) |>
        toEqual [{id: "1", text: "test1"}, {id: "2", text: "test2"}, {id: "3", text: "test3"}]
      }
      [@ocaml.warning "-10"]
  );

test
  "it should delete given note"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        Model.deleteNote "2";
        expect (Model.getNotes ()) |> toEqual [{id: "1", text: "test1"}, {id: "3", text: "test3"}]
      }
      [@ocaml.warning "-10"]
  );

test
  "it should not delete anything if wrong id is given"
  (
    fun () =>
      {
        Model.addNote {text: "test1"};
        Model.addNote {text: "test2"};
        Model.addNote {text: "test3"};
        Model.deleteNote "LOL WRONG ID";
        expect (Model.getNotes ()) |>
        toEqual [{id: "1", text: "test1"}, {id: "2", text: "test2"}, {id: "3", text: "test3"}]
      }
      [@ocaml.warning "-10"]
  );
