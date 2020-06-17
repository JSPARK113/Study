import $ from "jquery";

export default function module() {
  const Tools = {
    addTodoItem: function () {
      var todoItem = $("#new-todo-item").val();
      var $newTag = $("<li><input type='checkbox'" +
      " name='todo-item-done'" +
      " class='todo-item-done'" +
      " value='" +
      todoItem +
      "' /> " +
      todoItem +
      " <button class='todo-item-delete'>" +
      "Delete</button></li>")
      $newTag.find('input.todo-item-done').on('click', function(){
        $(this).parent().toggleClass("strike");
      })
      $("#todo-list").append($newTag);

      $("#new-todo-item").val("");
    },
    
    deleteTodoItem: function (e, item) {
      e.preventDefault();
      $(item)
        .parent()
        .fadeOut("slow", function () {
          $(item).parent().remove();
        });
    },
  };
  return Tools;
}
